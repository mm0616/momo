// 引入SoftwareSerial库，用于创建软串口通信
#include <SoftwareSerial.h>
#include <dht11.h>
#include <Servo.h>  //舵机库
Servo myservo;

//创建DHT11对象
dht11 DHT;
#define DHT11_PIN 3  //定义DHT11为数字口3

// 创建软串口对象，使用A5作为RX引脚接收数据，A4作为TX引脚发送数据
SoftwareSerial mySerial(A5, A4);

// 定义变量用于存储从语音模块接收到的控制码
volatile int Voice_Control = 0;  // 初始化为0，确保首次判断时不触发任何指令

// 用于存储从串口接收到的控制指令字符串
String WiFi_Control = "";

// 定义连接的引脚号
int servoPin = 5;
int redLedPin = 9;
int greenLedPin = 10;
int blueLedPin = 11;
int soilPin = A1;

/*
 函数功能：通过串口发送具有固定帧格式的数据包
 数据包格式：帧头(0xAA 0x55) + 消息号数据 + 数据1 + 数据2 + 帧尾(0x55 0xAA)
 
 输入参数说明：
  ---Message_Number ：消息号，用于标识命令类型   <必需填写>
  ---data1 ：第一个数据参数  <如果没有数据就输入0>
  ---data2 ：第二个数据参数  <如果没有数据就输入0>
 */
void Uart_SendCmd(int Message_Number, int data1, int data2) {
  // 发送帧头：固定字节0xAA和0x55，用于标识数据包的开始
  mySerial.write(0XAA);
  mySerial.write(0X55);

  // 发送消息号，标识具体的命令类型
  mySerial.write(Message_Number);

  // 发送两个数据参数
  mySerial.write(data1);
  mySerial.write(data2);

  // 发送帧尾：固定字节0x55和0xAA，用于标识数据包的结束
  mySerial.write(0X55);
  mySerial.write(0XAA);
}

void dht11_chk() {
  int chk;
  chk = DHT.read(DHT11_PIN);  // READ DATA
  switch (chk) {
    case DHTLIB_OK:
      break;
    case DHTLIB_ERROR_CHECKSUM:  //校检和错误返回
      break;
    case DHTLIB_ERROR_TIMEOUT:  //超时错误返回
      break;
    default:
      break;
  }
}

void setup() {
  // 初始化串口通信，波特率设置为750（注意：非标准波特率，需确保通信双方一致）
  Serial.begin(750);
  // 初始化软串口，用于与语音模块通信，波特率9600
  mySerial.begin(9600);

  // 将引脚设置为输入模式
  pinMode(DHT11_PIN, INPUT);
  pinMode(soilPin, INPUT);
  // 将LED引脚设置为输出模式
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  myservo.attach(servoPin);  //舵机连接数字口9
    //舵机旋转到180度
  myservo.write(180);
}

void loop() {
  //检查DHT11数据是否正常
  dht11_chk();
  //读取传感器数据
  int TempValue = DHT.temperature;
  int HumValue = DHT.humidity;
  int SoilValue = analogRead(soilPin);
  // 检查串口是否有数据可读
  if (Serial.available()) {
    // 读取直到换行符('\n')的数据，并转换为String类型
    WiFi_Control = Serial.readStringUntil('\n');

    // 去除字符串首尾的空白字符（如回车、空格等）
    WiFi_Control.trim();
    //发送传感器数据到ESP01-S模块，给网页显示
    if (WiFi_Control == "SENSOR_READ") {
      Serial.println("SOIL:" + String(SoilValue));
      Serial.println("TEMP:" + String(TempValue));
      Serial.println("HUM:" + String(HumValue));
    }
  }
  // 持续检查软串口是否有来自语音模块的数据
  while (mySerial.available()) {
    // 读取一个字节的数据
    Voice_Control = mySerial.read();

    // 将接收到的数据通过硬件串口输出，便于调试和监控
    Serial.println(Voice_Control);
  }

  if (Voice_Control == 1 || WiFi_Control == "RED_LED:1") {
    digitalWrite(redLedPin, HIGH);
    Serial.println("ACK:RED_LED:1");

  } else if (Voice_Control == 2 || WiFi_Control == "RED_LED:0") {
    digitalWrite(redLedPin, LOW);
    Serial.println("ACK:RED_LED:0");

  } else if (Voice_Control == 5 || WiFi_Control == "GREEN_LED:1") {
    digitalWrite(greenLedPin, HIGH);
    Serial.println("ACK:GREEN_LED:1");

  } else if (Voice_Control == 6 || WiFi_Control == "GREEN_LED:0") {
    digitalWrite(greenLedPin, LOW);
    Serial.println("ACK:GREEN_LED:0");

  } else if (Voice_Control == 7 || WiFi_Control == "BLUE_LED:1") {
    digitalWrite(blueLedPin, HIGH);
    Serial.println("ACK:BLUE_LED:1");

  } else if (Voice_Control == 8 || WiFi_Control == "BLUE_LED:0") {
    digitalWrite(blueLedPin, LOW);
    Serial.println("ACK:BLUE_LED:0");

  } else if ((WiFi_Control == "SERVO:1") || (Voice_Control == 17)) {
    myservo.write(180);
    Serial.println("ACK:SERVO:1");

  } else if ((WiFi_Control == "SERVO:0") || (Voice_Control == 18)) {
    myservo.write(0);
    Serial.println("ACK:SERVO:0");

  } else if (Voice_Control == 15 || WiFi_Control == "PUMP:1") {
    digitalWrite(A2, LOW);
    digitalWrite(A3, HIGH);
    Serial.println("ACK:PUMP:1");

  } else if (Voice_Control == 16 || WiFi_Control == "PUMP:0") {
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    Serial.println("ACK:PUMP:0");

  } else if (Voice_Control == 25) {
    // 指令码为25时发送消息号2，data1为温度值，data2为0
    Uart_SendCmd(2, TempValue, 0);

  } else if (Voice_Control == 26) {
    // 指令码为26时发送消息号3，data1为湿度值，data2为0
    Uart_SendCmd(3, HumValue, 0);
  } else if (Voice_Control == 30) {
    Uart_SendCmd(7, map(SoilValue, 0, 1023, 0, 100), 0);
  }
  // 清除指令字符串，避免重复执行
  WiFi_Control = "";
  Voice_Control = 0;
}