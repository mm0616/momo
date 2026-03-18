// 引入SoftwareSerial库，用于创建软串口
#include <SoftwareSerial.h>

// 创建软串口对象：RX引脚为A5，TX引脚为A4
// 用于连接语音识别模块
SoftwareSerial mySerial(A5, A4);
// 定义LED连接的引脚号（数字引脚3）
int ledPin = 3;

// 定义变量用于存储从语音模块接收到的控制码
volatile int Voice_Control = 0;  // 初始化为0，确保首次判断时不触发任何指令

void setup() {
  // 初始化硬件串口，用于调试输出，波特率9600
  Serial.begin(9600);
  // 初始化软串口，用于连接语音模块，波特率9600
  mySerial.begin(9600);
  // 将LED引脚设置为输出模式
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 检查软串口是否有来自语音模块的数据可读
  if (mySerial.available()) {
    // 从软串口读取一个字节的数据
    Voice_Control = mySerial.read();
    // 将接收到的数据通过硬件串口输出到串口监视器，便于调试
    Serial.println(Voice_Control);
  }
  // 根据接收到的指令值执行相应操作
  if (Voice_Control == 3) {
    // 当接收到值3时，点亮LED（高电平）
    digitalWrite(ledPin, HIGH);

  } else if (Voice_Control == 4) {
    // 当接收到值4时，熄灭LED（低电平）
    digitalWrite(ledPin, LOW);
  }
  // 清除指令，避免重复执行
  Voice_Control = 0;
}