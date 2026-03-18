/*
 * 文件名 : Voice-Controll-Smart-Farm
 * 功能   : 结合智能语音控制模块和所有传感器模拟语音控制智能农场系统
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

// 导入库文件
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h> 
#include <dht11.h> 
Servo myservo;  // 创建舵机对象来控制舵机,在ESP32上可以创建16个舵机对象

// 定义引脚常量
const int PhotoresistorPin = 34;  // 定义光敏传感器引脚
const int LED_PIN = 27;  // 定义LED引脚
const int SteamPin = 35;   // 定义水滴传感器引脚
const int BuzzerPin = 16; // 定义无源蜂鸣器引脚
const int MotorPin1 = 19; // (IN+)
const int MotorPin2 = 18; // (IN-)
const int TrigPin = 14; // trig接GPIO14
const int EchoPin = 13; // echo接GPIO13
const int ServoPin = 26; // 舵机的引脚
const int DHT11PIN = 17; // 温湿度传感器的引脚
const int SoilHumidityPin = 32;  // 定义土壤湿度传感器引脚
const int WaterLevelPin = 33;  // 定义水位传感器引脚
const int RelayPin = 25;  // 定义继电器引脚
const int RX_PIN = 23; // 引脚 GPIO23 为 RX
const int TX_PIN = 5; // 引脚 GPIO5 为 TX

SoftwareSerial mySerial(RX_PIN, TX_PIN); // 定义软件串口引脚（RX, TX）
LiquidCrystal_I2C lcd(0x27, 16, 2); // 定义LCD地址和行列
dht11 DHT11; // 初始化dht11

// LED亮度等级
const int LED_OFF = 0;
const int LED_DIM = 50;
const int LED_MEDIUM = 150;
const int LED_BRIGHT = 255;

// 定义变量
volatile int yuyin;
volatile int ReadValue;
volatile double AnalogValue;
volatile int Value1;
volatile int distance;
volatile int duration;
volatile int Temperature;
volatile int Humidity;
volatile double Soilhum;
volatile int Waterlevel;
volatile int Value2;

// 串口发送消息最大长度
#define UART_SEND_MAX      32
#define UART_MSG_HEAD_LEN  2
#define UART_MSG_FOOT_LEN  2

// 串口发送消息号
#define U_MSG_bozhensgshu      1
#define U_MSG_boxiaoshu      2
#define U_MSG_bobao1      3
#define U_MSG_bobao2      4
#define U_MSG_bobao3      5
#define U_MSG_bobao4      6
#define U_MSG_bobao5      7
#define U_MSG_bobao6      8
#define U_MSG_bobao7      9
#define U_MSG_bobao8      10
#define U_MSG_bobao9      11
#define U_MSG_bobao10      12
#define U_MSG_bobao11      13
#define U_MSG_bobao12      14
#define U_MSG_bobao13      15
#define U_MSG_bobao14      16
#define U_MSG_bobao15      17
#define U_MSG_bobao16      18
#define U_MSG_bobao17      19
#define U_MSG_bobao18      20

// 串口消息参数类型
typedef union {
  double d_double;
  int d_int;
  unsigned char d_ucs[8];
  char d_char;
  unsigned char d_uchar;
  unsigned long d_long;
  short d_short;
  float d_float;}uart_param_t;

// 串口发送函数实现
void _uart_send_impl(unsigned char* buff, int len) {
  // TODO: 调用项目实际的串口发送函数
  for(int i=0;i<len;i++){
    mySerial.write (*buff++);
  }
}

// 串口通信消息尾
const unsigned char g_uart_send_foot[] = {
  0x55, 0xaa
};

// 十六位整数转32位整数
void _int16_to_int32(uart_param_t* param) {
  if (sizeof(int) >= 4)
    return;
  unsigned long value = param->d_long;
  unsigned long sign = (value >> 15) & 1;
  unsigned long v = value;
  if (sign)
    v = 0xFFFF0000 | value;
  uart_param_t p;  p.d_long = v;
  param->d_ucs[0] = p.d_ucs[0];
  param->d_ucs[1] = p.d_ucs[1];
  param->d_ucs[2] = p.d_ucs[2];
  param->d_ucs[3] = p.d_ucs[3];
}

// 浮点数转双精度
void _float_to_double(uart_param_t* param) {
  if (sizeof(int) >= 4)
    return;
  unsigned long value = param->d_long;
  unsigned long sign = value >> 31;
  unsigned long M = value & 0x007FFFFF;
  unsigned long e =  ((value >> 23 ) & 0xFF) - 127 + 1023;
  uart_param_t p0, p1;
  p1.d_long = ((sign & 1) << 31) | ((e & 0x7FF) << 20) | (M >> 3);
  param->d_ucs[0] = p0.d_ucs[0];
  param->d_ucs[1] = p0.d_ucs[1];
  param->d_ucs[2] = p0.d_ucs[2];
  param->d_ucs[3] = p0.d_ucs[3];
  param->d_ucs[4] = p1.d_ucs[0];
  param->d_ucs[5] = p1.d_ucs[1];
  param->d_ucs[6] = p1.d_ucs[2];
  param->d_ucs[7] = p1.d_ucs[3];
}

// 串口通信消息头
const unsigned char g_uart_send_head[] = {
  0xaa, 0x55
};

//把获取超声波检测的距离，写在一个函数里
float getDistance() {
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);	//给trig至少10us的高电平时间触发
  digitalWrite(TrigPin,LOW);
  duration = pulseIn(EchoPin,HIGH);	//echo高电平的时间
  distance = duration/58;		//换算成距离，单位为cm
  delay(50);  
  return distance;
}
// 播报函数1
void _uart_bobao1() {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bobao1;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 3] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 5);
}

// 播报函数2
void _uart_bobao2() {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bobao2;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 3] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 5);
}
// 播报函数3
void _uart_bobao3() {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bobao3;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 3] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 5);
}

// 播报函数4
void _uart_bobao4() {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bobao4;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 3] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 5);
}

// 播报函数5
void _uart_bobao5() {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bobao5;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 3] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 5);
}

// 播报函数6
void _uart_bobao6() {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bobao6;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 3] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 5);
}

// 播报函数7
void _uart_bobao7() {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bobao7;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 3] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 5);
}

// 播报函数9
void _uart_bobao9() {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bobao9;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 3] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 5);
}

// 播报函数16
void _uart_bobao16() {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bobao16;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 3] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 5);
}

// 播报整数
void _uart_bozhensgshu(int zhengshu) {
  uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};
    for (i = 0; i < UART_MSG_HEAD_LEN; i++) {
        buff[i + 0] = g_uart_send_head[i];
    }
    buff[2] = U_MSG_bozhensgshu;
    param.d_int = zhengshu;
    _int16_to_int32(&param);
    buff[3] = param.d_ucs[0];
    buff[4] = param.d_ucs[1];
    buff[5] = 0;
    buff[6] = 0;
    for (i = 0; i < UART_MSG_FOOT_LEN; i++) {
        buff[i + 7] = g_uart_send_foot[i];
    }
    _uart_send_impl(buff, 9);
}

void setup(){
   Serial.begin(9600); // 硬件串口（与电脑通信）
   mySerial.begin(9600); // 软件串口（与外设通信）
   ReadValue = 0; // 定义变量ReadValue初始值为0
   distance = 0; // 定义变量distance初始值为0 
   yuyin = 0;  // 定义变量yuyin初始值为0 
   AnalogValue = 0; // 定义变量AnalogValue初始值为0
   Value1 = 0; // 定义变量Value1初始值为0
   Temperature = 0; // 定义变量Temperature初始值为0
   Humidity = 0; // 定义变量Humidity初始值为0
   Soilhum = 0; // 定义变量Soilhum初始值为0 
   Waterlevel = 0; // 定义变量Waterlevel初始值为0 
   Value2 = 0; // 定义变量Value2初始值为0 
   Wire.begin(21,22); // 定义LCD通信引脚
   lcd.init(); // 初始化LCD
   lcd.backlight(); // 打开LCD背光
   lcd.display(); // 打开LCD显示
   lcd.clear(); // LCD清屏
   pinMode(SteamPin, INPUT); // 设置水滴传感器引脚为输入模式
   pinMode(BuzzerPin, OUTPUT); // 设置蜂鸣器引脚为输出模式
   pinMode(PhotoresistorPin, INPUT); // 设置光敏引脚为输入模式
   pinMode(MotorPin1,OUTPUT); // 设置MotorPin1(IN+)引脚为输出模式
   pinMode(MotorPin2,OUTPUT); // 设置MotorPin2(IN-)引脚为输出模式
   pinMode(LED_PIN, OUTPUT); // 设置LED引脚为输出模式
   pinMode(TrigPin,OUTPUT);  // trig设置为输出模式
   pinMode(EchoPin,INPUT);   // echo设置为输入模式
   pinMode(SoilHumidityPin,INPUT);
   pinMode(WaterLevelPin,INPUT);
   pinMode(RelayPin,OUTPUT);
   myservo.attach(ServoPin);   // 将引脚io26上的舵机连接到舵机对象上
   myservo.write(180); // 舵机角度为180°
   delay(1000); // 延时1s
   //配置LEDC渠道
   ledcAttachChannel(BuzzerPin, 1000, 8, 4);
}

void loop(){
    //获取温湿度数据
   int chk = DHT11.read(DHT11PIN); 
   Temperature = DHT11.temperature;
   Humidity = DHT11.humidity;
   ReadValue = analogRead(PhotoresistorPin); // 读取光敏传感器的模拟值
   AnalogValue = analogRead(SteamPin); // 获取水滴传感器的模拟值
   Value1 = round((AnalogValue / 4096.0) * 100); //将传感器模拟值通过计算转化成百分数赋于变量Value1
   Soilhum = analogRead(32); // 存储读取到的土壤湿度模拟值
   Waterlevel = analogRead(33); // 存储读取到的水位模拟值
   Value2 = round((Soilhum / 4096.0) * 100); // 将土壤湿度模拟值通过计算转化成百分数赋于变量Value2
   distance = getDistance();
   lcd.setCursor(1, 0);
   lcd.print("Voice Controll");
   // 在LCD对应位置显示湿度相关信息
   lcd.setCursor(3, 1);
   lcd.print("Smart Farm");
   if (mySerial.available() > 0) { // 接收语音控制模块的外设数据(命令参数)
     yuyin = mySerial.read(); // 将接收到的外设数据(命令参数)进行赋值
     Serial.println(yuyin);  // 串口打印收到的外设数据(命令参数)
     if (yuyin == 1) { // 接收到的外设数据(命令参数)为1, 打开LED,灯的亮度为150
       analogWrite(LED_PIN, LED_MEDIUM);
    }
     if (yuyin == 2) { // 接收到的数据为2,关闭灯
       analogWrite(LED_PIN, LED_OFF);
    }
     if (yuyin == 3) { // 接收到的数据为3,灯的亮度为最亮
       analogWrite(LED_PIN, LED_BRIGHT); 
    } 
     if (yuyin == 4) { // 接收到的数据为4,灯的亮度为暗
       analogWrite(LED_PIN, LED_DIM); 
    }
     if (yuyin == 5) { // 接收到的外设数据(命令参数)为5, 打开风扇, 风速为100
       analogWrite(MotorPin1, 100);
       analogWrite(MotorPin2, 0);
    }
     if (yuyin == 7) { // 接收到的外设数据(命令参数)为7, 风大一点, 风速为200
       analogWrite(MotorPin1, 200);
       analogWrite(MotorPin2, 0);
    }
     if (yuyin == 8) { // 接收到的外设数据(命令参数)为8, 风小一点, 风速为100
       analogWrite(MotorPin1, 100);
       analogWrite(MotorPin2, 0);
    }
     if (yuyin == 6) { // 接收到的外设数据(命令参数)为6, 关闭风扇
       analogWrite(MotorPin1, 0);
       analogWrite(MotorPin2, 0);
    }
     if (yuyin == 11) { // 接收到的外设数据(命令参数)为11, 播放音乐
       ledcWriteTone(BuzzerPin, 262);
       delay(200);
       ledcWriteTone(BuzzerPin, 294);
       delay(200);
       ledcWriteTone(BuzzerPin, 330);
       delay(200);
       ledcWriteTone(BuzzerPin, 349);
       delay(200);
       ledcWriteTone(BuzzerPin, 392);
       delay(200);
       ledcWriteTone(BuzzerPin, 440);
       delay(200);
       ledcWriteTone(BuzzerPin, 494);
       delay(200);
       ledcWriteTone(BuzzerPin, 0);
       delay(200);
    }
     if (yuyin == 12) { // 接收到的外设数据(命令参数)为12, 关闭音乐
       ledcWriteTone(BuzzerPin, 0);
    }
     if (yuyin == 34) { // 接收到的外设数据(命令参数)为34, 开始喂食
       myservo.write(80); // 舵机角度为80°
       delay(1000); // 延时1s
    }
     if (yuyin == 35) { // 接收到的外设数据(命令参数)为35, 停止喂食
       myservo.write(180); // 舵机角度为180°
       delay(1000); // 延时1s
    }
     if (yuyin == 47) { // 进行判断，接收到的外设数据(命令参数)为47，检测温度并且进行语音播报
        yuyin = 0;
        delay(2000);
        _uart_bobao1();
        delay(2000);
        _uart_bozhensgshu(Temperature);
        delay(2000);
        _uart_bobao2();
        delay(2000);
    }
     if (yuyin == 48) { // 进行判断，接收到的外设数据(命令参数)为48，检测湿度并且进行语音播报
        yuyin = 0;
        delay(2000);
        _uart_bobao4();
        delay(2000);
        _uart_bozhensgshu(Humidity);
        delay(2000);
    }
     if (yuyin == 50) { // 进行判断，接收到的数据(命令参数)为50，检测光照强度并且进行语音播报
       yuyin = 0;
       delay(3000);
       _uart_bobao5();
       delay(3000);
       _uart_bozhensgshu(ReadValue);
       delay(2000);
    }
     if (yuyin == 49) { // 进行判断，接收到的数据(命令参数) 为49，检测雨水量的百分数值并且进行语音播报
       yuyin = 0;
       delay(3000);
       _uart_bobao3();
       delay(3000);
       _uart_bozhensgshu(Value1);
       delay(2000);
    }
     if (yuyin == 54) {// 进行判断，接收到的外设数据(命令参数)为54，检测距离并且进行语音播报
       yuyin = 0;
       delay(2000);
       _uart_bobao9();
       delay(2000);
       _uart_bozhensgshu(distance);
       delay(1000);
       _uart_bobao16();
       delay(2000);
    }
     if (yuyin == 51) { // 进行判断，接收到的外设数据(命令参数)为51，检测土壤湿度百分数值并且进行语音播报
       yuyin = 0;
       delay(3000);
       _uart_bobao6();
       delay(3000);
       _uart_bozhensgshu(Value2);
       delay(2000);
    }
     if (yuyin == 52) { // 进行判断，接收到的外设数据(命令参数)为52，检测水池水位模拟值并且进行语音播报
       yuyin = 0;
       delay(2000);
       _uart_bobao7();
       delay(2000);
       _uart_bozhensgshu(Waterlevel);
       delay(2000);
     }
   } 
    if (Value2 <= 15 && Waterlevel >= 800) {//土壤湿度百分数值低于设定的阈值时，且水池里的水源充足，语音控制抽水系统进行灌溉
      ledcWriteTone(BuzzerPin, 494);
      delay(200);
      if (yuyin == 9) { // 进行判断，接收到的外设数据(命令参数)为9，继电器控制水泵抽水
        yuyin = 0;
        delay(1000);
        digitalWrite(RelayPin,HIGH); // 打开继电器
        delay(400); // 灌溉的延时
        digitalWrite(RelayPin,LOW); // 关闭继电器
        delay(700);
     }
   }
   ledcWriteTone(BuzzerPin, 0); 
}
