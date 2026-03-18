/*  
 * 名称   : WiFi-APP-Smart-Farm
 * 功能   : 使用 wifi+APP 一起控制智能农场
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/ 
*/

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <dht11.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

// 显示
#define DHT11PIN 17         // 温湿度传感器引脚
#define RAINWATERPIN 35     // 水滴传感器引脚
#define LIGHTPIN 34         // 光敏电阻引脚
#define WATERLEVELPIN 33    // 水位传感器引脚
#define SOILHUMIDITYPIN 32  // 土壤湿度传感器引脚
// 控制
#define LEDPIN 27     // LED引脚
#define RELAYPIN 25    // 继电器引脚控制水泵
#define SERVOPIN 26   // 舵机引脚
#define MotorPIN1 19  // 电机模块IN+引脚
#define MotorPIN2 18  // 电机模块IN-引脚
#define BUZZERPIN 16  // 蜂鸣器引脚

/*替换为您的网络凭据（输入您自己的WiFi名称和密码）*/
const char* ssid = "REPLACE_WITH_YOUR_SSID";  // 输入你自己的WiFi名称
const char* password = "REPLACE_WITH_YOUR_PASSWORD"; // 输入你自己的WiFi密码

// 初始化LCD1602, I2C地址为0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiServer server(80);  // 初始化wifi服务器
dht11 DHT11;            // 初始化温湿度传感器
Servo myservo;          // 创建舵机对象控制舵机
                        // 在ESP32上可以创建16个舵机对象

// 将变量定义为检测到的值
String request;
String dataBuffer;
int Temperature;   // 温度
int Humidity;      // 湿度
int SoilHumidity;  // 土壤湿度
int Light;         // 亮度
int WaterLevel;    // 水位
int Rainwater;     // 雨水

void setup() {
  Serial.begin(9600);
  // 连接wifi
  WiFi.begin(ssid, password);
  // 检查是否连接
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  delay(1000);
  // 串口打印wifi名称和IP地址
  Serial.println("Connected to WiFi");
  Serial.print("WiFi NAME:");
  Serial.println(ssid);
  Serial.print("IP:");
  Serial.println(WiFi.localIP());

  // 初始化LCD
  lcd.init();
  // 打开/关闭（可选）背光
  lcd.backlight();
  //lcd.noBacklight();
  lcd.clear();
  // 设置光标的位置
  lcd.setCursor(0, 0);
  // LCD打印
  lcd.print("IP:");
  // 设置光标的位置
  lcd.setCursor(0, 1);
  // LCD打印
  lcd.print(WiFi.localIP());

  // 设置引脚模式
  pinMode(LEDPIN, OUTPUT);
  pinMode(RAINWATERPIN, INPUT);
  pinMode(LIGHTPIN, INPUT);
  pinMode(SOILHUMIDITYPIN, INPUT);
  pinMode(WATERLEVELPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(MotorPIN1, OUTPUT);
  pinMode(MotorPIN2, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  delay(1000);

  // 连接舵机到引脚26
  myservo.attach(SERVOPIN);
  myservo.write(180);
  delay(1000);

  // 启动服务器
  server.begin();

  // 配置LEDC渠道
  ledcAttachChannel(BUZZERPIN, 1000, 8, 4);
}

void loop() {
  // 检查客户端与web服务器是否连接
  // 当客户端连接到服务器时，“server.available（）”返回一个用于客户端通信的WiFiClient对象。
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      // 确定服务器是否发送数据
      if (client.available()) {
        request = client.readStringUntil('s');
        Serial.print("Received message: ");
        Serial.println(request);
      }
      // 获取所有传感器数据
      getSensorsData();
      // 将所有数据放入数据缓冲器"dataBuffer"
      dataBuffer = "";
      dataBuffer += String(Temperature, HEX);
      dataBuffer += String(Humidity, HEX);
      dataBuffer += dataHandle(SoilHumidity);
      dataBuffer += dataHandle(Light);
      dataBuffer += dataHandle(WaterLevel);
      dataBuffer += dataHandle(Rainwater);
      // 发送数据到服务器，传输到APP
      client.print(dataBuffer);
      delay(500);

      //LED
      if (request == "a") {
        digitalWrite(LEDPIN, HIGH);
      } else if (request == "A") {
        digitalWrite(LEDPIN, LOW);
      }
      // 灌溉
      else if (request == "b") {
        digitalWrite(RELAYPIN, HIGH);
        delay(400);  //灌溉延时
        digitalWrite(RELAYPIN, LOW);
        delay(700);
      }
      // 风扇
      else if (request == "c") {
        delay(800);
        digitalWrite(MotorPIN2, LOW);
        analogWrite(MotorPIN1, 100);
        delay(200);
      } else if (request == "C") {
        digitalWrite(MotorPIN2, LOW);
        analogWrite(MotorPIN1, 0);
      }
      // 喂食盒
      else if (request == "d") {
        // 舵机转到80°打开喂食盒
        myservo.write(80);
        delay(1000);
      } else if (request == "D") {
        // 舵机转到180°合上喂食盒
        myservo.write(180);
        delay(1000);
      }
      // 蜂鸣器播放音乐
      else if (request == "e") {
        ledcWriteTone(BUZZERPIN, 262);
        delay(200);
        ledcWriteTone(BUZZERPIN, 294);
        delay(200);
        ledcWriteTone(BUZZERPIN, 330);
        delay(200);
        ledcWriteTone(BUZZERPIN, 349);
        delay(200);
        ledcWriteTone(BUZZERPIN, 392);
        delay(200);
        ledcWriteTone(BUZZERPIN, 440);
        delay(200);
        ledcWriteTone(BUZZERPIN, 494);
        delay(200);
        ledcWriteTone(BUZZERPIN, 0);
        delay(500);
      }
      request = "";
    }
    Serial.println("Client disconnected");
  }
}

void getSensorsData() {
  // 获取数据
  int chk = DHT11.read(DHT11PIN);
  // 水滴传感器
  Rainwater = analogRead(RAINWATERPIN);
  // 光敏电阻
  Light = analogRead(LIGHTPIN);
  // 土壤湿度传感器
  SoilHumidity = analogRead(SOILHUMIDITYPIN) * 1.8;
  // 水位传感器
  WaterLevel = analogRead(WATERLEVELPIN) * 1.8;
  // 温度
  Temperature = DHT11.temperature;
  // 湿度
  Humidity = DHT11.humidity;
}

// 将数据转换成百分比
String dataHandle(int data) {
  // 将模拟值转换为百分比
  int percentage = (data / 4095.0) * 100;
  // 如果转换后的百分比大于100，则输出100
  percentage = percentage > 100 ? 100 : percentage;
  // 六个字符存储十六进制字符串，一个字符作为终止符
  char hexString[3];
  // 将十六进制值转换为6位十六进制字符串，加上前导零：0表示00,1表示01…
  sprintf(hexString, "%02X", percentage);

  return hexString;
}
