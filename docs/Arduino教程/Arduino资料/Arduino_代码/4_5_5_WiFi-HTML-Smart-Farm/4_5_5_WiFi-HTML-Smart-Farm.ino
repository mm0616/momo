/*  
 * 名称   : WiFi-HTML-Smart-Farm
 * 功能   : 使用wifi网页控制智慧农场
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/ 
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>
#include <ESP32Servo.h>

// 设置引脚
#define DHT11PIN        17  // 温湿度传感器引脚
#define LEDPIN          27  // LED引脚
#define SERVOPIN        26  // 舵机引脚
#define MotorPIN1       19  // 电机模块IN+引脚
#define MotorPIN2       18  // 电机模块IN-引脚
#define STEAMPIN        35  // 水滴传感器引脚
#define LIGHTPIN        34  // 光敏传感器引脚
#define SOILHUMIDITYPIN 32  // 土壤湿度传感器引脚
#define WATERLEVELPIN   33  // 水位传感器引脚
#define RELAYPIN        25   // 继电器引脚
#define BUZZERPIN       16  // 无源蜂鸣器引脚

// 初始化模块
dht11 DHT11;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;  // 设置舵机对象控制舵机

/*替换为您的网络凭据（输入您自己的WiFi名称和密码）*/
const char* ssid = "REPLACE_WITH_YOUR_SSID";  // 输入你自己的WiFi名称
const char* password = "REPLACE_WITH_YOUR_PASSWORD"; // 输入你自己的WiFi密码

// 创建WebServer对象
WebServer server(80);

// 控制状态的变量
static int A = 0;
static int B = 0;
static int C = 0;

// HTML网页内容
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<title>TEST HTML ESP32</title>
<head>
  <meta charset="utf-8">
  <style>
    html, body {
      margin: 0;
      width: 100%;
      height: 100%;
      display: flex;
      justify-content: center;
      align-items: center;
      flex-direction: column;
      background-color: #f0f0f0;
    }

    /* 主按钮容器 */
    .btn {
      display: flex;
      justify-content: center;  /* 按钮居中 */
      gap: 10px;  /* 增加按钮之间的空格 */
      width: 320px;  /* 设置宽度以确保按钮紧密排列 */
      flex-wrap: wrap; /* 如果需要，允许按钮换行 */
      margin-bottom: 20px;  /* 按钮和数据显示之间的空格 */
    }

    /* 按钮样式 */
    .btn button {
      width: 70px;  /* 设置按钮宽度 */
      height: 70px;  /* 设置按钮高度 */
      border: none;
      font-size: 16px;
      color: #fff;
      background-color: #89e689;
      cursor: pointer;
    }

    .btn button:active {
      top: 2px;
    }

    /* 数据显示区 */
    #dht {
      text-align: center;  /* 文字居中 */
      width: 320px;  /* 与按钮容器的宽度相同 */
      color: #fff;
      background-color: #47a047;
      font-size: 18px; /* 调整字体大小以提高可读性 */
      padding: 10px;
      border-radius: 10px;  /* 圆角 */
      box-sizing: border-box;
      margin-bottom: 10px; /* 在数据显示和按钮之间增加空格 */
    }

  </style>
</head>
<body>

  <!-- Display area for sensor data -->
  <div id="dht"></div>

  <!-- Button row -->
  <div class="btn">
    <button id="btn-led" onclick="setLED()">LED灯</button>
    <button id="btn-fan" onclick="setFan()">风扇</button>
    <button id="btn-feeding" onclick="setFeeding()">喂养</button>
    <button id="btn-watering" onclick="setWatering()">抽水</button>
    <button id="btn-music" onclick="setmusic()">音乐</button>
  </div>

  <script>
    function setLED() {
      var payload = "A"; 
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/set?value=" + payload, true);
      xhr.send();
    }
    function setFan() {
      var payload = "B"; 
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/set?value=" + payload, true);
      xhr.send();
    }
    function setFeeding() {
      var payload = "C"; 
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/set?value=" + payload, true);
      xhr.send();
    }
    function setWatering() {
      var payload = "D"; 
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/set?value=" + payload, true);
      xhr.send();
    }
    function setmusic() {
      var payload = "E"; 
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/set?value=" + payload, true);
      xhr.send();
    }

    setInterval(function () {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("dht").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/dht", true);
      xhttp.send();
    }, 1000)
  </script>

</body>
</html>

)rawliteral";

// 将传感器数据合并为HTML格式
String Merge_Data(void) {
  String dataBuffer;
  String Humidity;
  String Temperature;
  String Steam;
  String Light;
  String SoilHumidity;
  String WaterLevel;
  
  // 读取DHT11传感器
  int chk = DHT11.read(DHT11PIN);
  
  // 读取其他传感器
  Steam = String(analogRead(STEAMPIN) / 4095.0 * 100);
  Light = String(analogRead(LIGHTPIN));
  int shvalue = analogRead(SOILHUMIDITYPIN) / 4095.0 * 100 * 2.3;
  shvalue = shvalue > 100 ? 100 : shvalue;
  SoilHumidity = String(shvalue);
  int wlvalue = analogRead(WATERLEVELPIN) / 4095.0 * 100 * 2.5;
  wlvalue = wlvalue > 100 ? 100 : wlvalue;
  WaterLevel = String(wlvalue);
  Temperature = String(DHT11.temperature);
  Humidity = String(DHT11.humidity);
  
  // 构建HTML内容
  dataBuffer += "<p>";
  dataBuffer += "<h1>传感器数据</h1>";
  dataBuffer += "<b>温度: </b><b>" + Temperature + "</b><b>℃</b><br/>";
  dataBuffer += "<b>湿度: </b><b>" + Humidity + "</b><b>%RH</b><br/>";
  dataBuffer += "<b>水位: </b><b>" + WaterLevel + "</b><b>%</b><br/>";
  dataBuffer += "<b>雨量: </b><b>" + Steam + "</b><b>%</b><br/>";
  dataBuffer += "<b>光强: </b><b>" + Light + "</b><br/>";
  dataBuffer += "<b>土壤湿度: </b><b>" + SoilHumidity + "</b><b>%</b><br/>";
  dataBuffer += "</p>";

  return dataBuffer;
}

// 根据收到的HTTP请求配置操作
void Config_Callback() {
  if (server.hasArg("value")) {
    String HTTP_Payload = server.arg("value");
    Serial.printf("[%lu]%s\r\n", millis(), HTTP_Payload.c_str());

    if (HTTP_Payload == "A") {
      if (A) {
        digitalWrite(LEDPIN, LOW);
        A = 0;
      } else {
        digitalWrite(LEDPIN, HIGH);
        A = 1;
      }
    }

    if (HTTP_Payload == "B") {
      if (B) {
        digitalWrite(MotorPIN1, LOW);
        digitalWrite(MotorPIN2, LOW);
        B = 0;
      } else {
        delay(500);
        digitalWrite(MotorPIN1, HIGH);
        digitalWrite(MotorPIN2, LOW);
        delay(500);
        B = 1;
      }
    }

    if (HTTP_Payload == "C") {
      if (C) {
        myservo.write(180);
        delay(1000);
        C = 0;
      } else {
        myservo.write(80);
        delay(1000);
        C = 1;
      }
    }

    if (HTTP_Payload == "D") {
      digitalWrite(RELAYPIN, HIGH);
      delay(400);
      digitalWrite(RELAYPIN, LOW);
      delay(700);
    }
    if (HTTP_Payload == "E") {
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
  }
  server.send(200, "text/plain", "OK");
}

// 处理无效的URL访问
void notFound() {
  server.send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(9600);
  
  // 连接WiFi
  WiFi.begin(ssid, password);
  while (!WiFi.isConnected()) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected..!");
  Serial.println("Got IP: ");
  Serial.println(WiFi.localIP());

  // 设置引脚模式
  pinMode(LEDPIN, OUTPUT);
  pinMode(STEAMPIN, INPUT);
  pinMode(LIGHTPIN, INPUT);
  pinMode(SOILHUMIDITYPIN, INPUT);
  pinMode(WATERLEVELPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(MotorPIN1, OUTPUT);
  pinMode(MotorPIN2, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);

  delay(1000);

  // 连接舵机引脚
  myservo.attach(SERVOPIN);
  myservo.write(180);
  delay(1000);

 //配置LEDC渠道
  ledcAttachChannel(BUZZERPIN, 1000, 8, 4);

  // 初始化LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IP:");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  // 设置服务器路由器
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", index_html);
  });

  server.on("/dht", HTTP_GET, []() {
    server.send(200, "text/plain", Merge_Data().c_str());
  });

  server.on("/set", HTTP_GET, Config_Callback);
  server.onNotFound(notFound);

  // 启动服务器
  server.begin();
}

void loop() {
  server.handleClient();
}
