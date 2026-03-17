// 引入SoftwareSerial库，用于创建软串口通信
#include <SoftwareSerial.h>

// 创建软串口对象，使用A5作为RX引脚接收数据，A4作为TX引脚发送数据
// 通常用于连接语音识别模块
SoftwareSerial mySerial(A5, A4);

// 定义变量用于存储从语音模块接收到的控制码
volatile int Voice_Control = 0;  // 初始化为0，确保首次判断时不触发任何指令

// 字符串变量，用于存储从WiFi模块（通过硬件串口）接收到的指令
String WiFi_Control = "";

// 定义LED连接的引脚号
int redLedPin = 9;
int greenLedPin = 10;
int blueLedPin = 11;

void setup() {
  // 初始化硬件串口，波特率设置为750（非标准值，需确保与WiFi模块一致）
  Serial.begin(750);

  // 初始化软串口，波特率9600，用于与语音模块通信
  mySerial.begin(9600);

  // 设置三色LED控制引脚为输出模式
  pinMode(redLedPin, OUTPUT);    // 红色LED
  pinMode(greenLedPin, OUTPUT);  // 绿色LED
  pinMode(blueLedPin, OUTPUT);   // 蓝色LED
}

void loop() {
  // 持续检查软串口是否有来自语音模块的数据
  while (mySerial.available()) {
    // 读取一个字节的数据（语音模块发送的通常是整数值）
    Voice_Control = mySerial.read();

    // 将接收到的语音指令通过硬件串口打印，便于调试
    Serial.print("Voice_Control:");
    Serial.println(Voice_Control);
  }

  // 检查硬件串口是否有来自WiFi模块的数据
  if (Serial.available()) {
    // 读取直到换行符的字符串（WiFi指令通常以换行结束）
    WiFi_Control = Serial.readStringUntil('\n');

    // 去除字符串首尾的空白字符（如回车、空格等）
    WiFi_Control.trim();

    // 将接收到的WiFi指令回传，便于调试
    Serial.print("WiFi_Control:");
    Serial.println(WiFi_Control);
  }

  // 根据语音指令或WiFi指令控制LED状态
  // 使用逻辑或（||）实现两种控制源均可触发相同动作

  // 控制红色LED：指令1 或 "RED_LED:1" 点亮
  if (Voice_Control == 1 || WiFi_Control == "RED_LED:1") {
    digitalWrite(redLedPin, HIGH);    // 点亮红色LED
    Serial.println("ACK:RED_LED:1");  // 发送确认信息

    // 控制红色LED：指令2 或 "RED_LED:0" 熄灭
  } else if (Voice_Control == 2 || WiFi_Control == "RED_LED:0") {
    digitalWrite(redLedPin, LOW);
    Serial.println("ACK:RED_LED:0");

    // 控制绿色LED：指令5 或 "GREEN_LED:1" 点亮
  } else if (Voice_Control == 5 || WiFi_Control == "GREEN_LED:1") {
    digitalWrite(greenLedPin, HIGH);
    Serial.println("ACK:GREEN_LED:1");

    // 控制绿色LED：指令6 或 "GREEN_LED:0" 熄灭
  } else if (Voice_Control == 6 || WiFi_Control == "GREEN_LED:0") {
    digitalWrite(greenLedPin, LOW);
    Serial.println("ACK:GREEN_LED:0");

    // 控制蓝色LED：指令7 或 "BLUE_LED:1" 点亮
  } else if (Voice_Control == 7 || WiFi_Control == "BLUE_LED:1") {
    digitalWrite(blueLedPin, HIGH);
    Serial.println("ACK:BLUE_LED:1");

    // 控制蓝色LED：指令8 或 "BLUE_LED:0" 熄灭
  } else if (Voice_Control == 8 || WiFi_Control == "BLUE_LED:0") {
    digitalWrite(blueLedPin, LOW);
    Serial.println("ACK:BLUE_LED:0");
  }

  // 清除当前指令，避免重复执行
  WiFi_Control = " ";  // 注意：赋值为空格字符串，建议改为空字符串""
  Voice_Control = 0;   // 语音指令清零
}