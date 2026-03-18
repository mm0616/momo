// 引入SoftwareSerial库，用于创建软串口通信
#include <SoftwareSerial.h>

// 创建软串口对象，使用A5作为RX引脚接收数据，A4作为TX引脚发送数据
SoftwareSerial mySerial(A5, A4);

// 定义变量用于存储从语音模块接收到的控制码
volatile int Voice_Control = 0;  // 初始化为0，确保首次判断时不触发任何指令

// 用于存储从串口接收到的控制指令字符串
String WiFi_Control = "";



void setup() {
  // 初始化串口通信，波特率设置为750（注意：非标准波特率，需确保通信双方一致）
  Serial.begin(750);
  // 初始化软串口，用于与语音模块通信，波特率9600
  mySerial.begin(9600);

  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}

void loop() {
  // 检查串口是否有数据可读
  if (Serial.available()) {
    // 读取直到换行符('\n')的数据，并转换为String类型
    WiFi_Control = Serial.readStringUntil('\n');

    // 去除字符串首尾的空白字符（如回车、空格等）
    WiFi_Control.trim();

    // 将接收到的指令回传到串口，便于调试
    Serial.print("WiFi_Control:");
    Serial.println(WiFi_Control);
  }
  // 持续检查软串口是否有来自语音模块的数据
  while (mySerial.available()) {
    // 读取一个字节的数据
    Voice_Control = mySerial.read();

    // 将接收到的数据通过硬件串口输出，便于调试和监控
    Serial.println(Voice_Control);
  }

  // 判断接收到的指令内容并执行相应操作
  if ((WiFi_Control == "PUMP:1") || (Voice_Control == 15)) {
    //水泵工作
    digitalWrite(A2, LOW);
    digitalWrite(A3, HIGH);
    // 发送应答指令到串口
    Serial.println("ACK:PUMP:1");

  } else if ((WiFi_Control == "PUMP:0") || (Voice_Control == 16)) {
    //水泵停止工作
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    // 发送应答指令到串口
    Serial.println("ACK:PUMP:0");
  }
  // 清除指令字符串，避免重复执行
  WiFi_Control = "";
  Voice_Control = 0;
}