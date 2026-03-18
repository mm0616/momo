/*
 * 文件名 : Auto-Irrigation
 * 功能   : 结合水位传感器，土壤湿度传感器，LCD1602、继电器、蜂鸣器、智能语音模块和水泵模拟自动灌溉系统
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/
// 导入相关库文件
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 定义引脚常量
const int BuzzerPin = 16;  // 定义蜂鸣器引脚
const int SoilHumidityPin = 32;  // 定义土壤湿度传感器引脚
const int WaterLevelPin = 33;  // 定义水位传感器引脚
const int RelayPin = 25;  // 定义继电器引脚
const int RX_PIN = 23; // 引脚 GPIO23 为 RX
const int TX_PIN = 5; // 引脚 GPIO5 为 TX

LiquidCrystal_I2C lcd(0x27,16,2); // 定义LCD地址和行列
SoftwareSerial mySerial(RX_PIN, TX_PIN); // 定义软件串口引脚（RX, TX）

// 定义变量
volatile double Soilhum;
volatile int Waterlevel;
volatile int Value;
volatile int yuyin;

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

void setup(){
   Serial.begin(9600); // 硬件串口（与电脑通信）
   mySerial.begin(9600); // 软件串口（与外设通信）
   Soilhum = 0; // 定义变量Soilhum初始值为0 
   Waterlevel = 0; // 定义变量Waterlevel初始值为0 
   Value = 0; // 定义变量Value初始值为0 
   yuyin = 0;  // 定义变量yuyin初始值为0
   Wire.begin(21,22); // 打开LCD通信引脚
   lcd.init();   // LCD初始化
   lcd.backlight(); // 开启LCD背光
   lcd.display();  //打开LCD显示
   lcd.clear(); // 清除LCD上显示的信息
   // 设置引脚模式
   pinMode(BuzzerPin,OUTPUT);
   pinMode(SoilHumidityPin,INPUT);
   pinMode(WaterLevelPin,INPUT);
   pinMode(RelayPin,OUTPUT);
}

void loop(){
   Soilhum = analogRead(32); // 存储读取到的土壤湿度模拟值
   Waterlevel = analogRead(33); // 存储读取到的水位模拟值
   Value = round((Soilhum / 4096.0) * 100); // 将土壤湿度模拟值通过计算转化成百分数赋于变量Value
   // 在LCD相应位置显示土壤湿度百分数和水位模拟值等信息
   lcd.setCursor(0, 0);
   lcd.print(String("SoilHum(%):") + String(Value));
   lcd.setCursor(0, 1);
   lcd.print(String("WaterLevel:") + String(Waterlevel));
   if (mySerial.available() > 0) { // 接收语音控制模块的外设数据(命令参数)
     yuyin = mySerial.read(); // 将接收到的外设数据(命令参数)进行赋值
     Serial.println(yuyin); // 串口打印收到的外设数据(命令参数)
     if (yuyin == 51) { // 进行判断，接收到的外设数据(命令参数)为51，检测土壤湿度百分数值并且进行语音播报
       yuyin = 0;
       delay(3000);
       _uart_bobao6();
       delay(3000);
       _uart_bozhensgshu(Value);
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
   if (Value <= 15) { // 进行判断，土壤湿度百分数值小于等于15，蜂鸣器发出警报声1
     tone(BuzzerPin,659);
     delay(100);
     tone(BuzzerPin,880);
     delay(100);
     tone(BuzzerPin,988);
     delay(100);
     noTone(BuzzerPin);  //关闭
   }
   if (Waterlevel <= 600) { // 进行判断，上传水位模拟值小于等于600，蜂鸣器发出警报声2
     tone(BuzzerPin,147);
     delay(100);
     tone(BuzzerPin,175);
     delay(100);
     tone(BuzzerPin,220);
     delay(100);
     noTone(BuzzerPin);  //关闭
   }
   if (Value <= 15 && Waterlevel >= 800) {//土壤湿度百分数值低于设定的阈值时，且水池里的水源充足，抽水系统会进行自动灌溉
     digitalWrite(RelayPin,HIGH);
     delay(400);//灌溉的延时
     digitalWrite(RelayPin,LOW);
     delay(700);
   }
   delay(500);
   lcd.clear(); // 清除LCD显示
}
