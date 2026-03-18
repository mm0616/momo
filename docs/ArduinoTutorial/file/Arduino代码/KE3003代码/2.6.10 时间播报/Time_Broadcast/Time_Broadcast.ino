// 引入SoftwareSerial库，用于创建软串口通信
#include <SoftwareSerial.h>
//DS3231时钟模块的库
#include <RtcDS3231.h>
#include <SoftwareWire.h>

// 创建软串口对象，使用A5作为RX引脚接收数据，A4作为TX引脚发送数据
SoftwareSerial mySerial(A3, A2);

// 定义变量用于存储从语音模块接收到的控制码
volatile int Voice_Control = 0;  // 初始化为0，确保首次判断时不触发任何指令

SoftwareWire myWire(A4, A5);  //i2c接口
RtcDS3231<SoftwareWire> Rtc(myWire);


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

void setup() {
  // 初始化硬件串口，用于调试和监控，波特率9600
  Serial.begin(9600);

  // 初始化软串口，用于与语音模块通信，波特率9600
  mySerial.begin(9600);
  //初始化时钟模块函数
  Rtc.Begin();
  Rtc.SetIsRunning(true);
  Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
}

void loop() {
  //获取时间数据
  int hour = Rtc.GetDateTime().Hour();
  int min = Rtc.GetDateTime().Minute();

  Serial.print(hour);
  Serial.print(":");
  Serial.println(min);

  // 持续检查软串口是否有来自语音模块的数据
  while (mySerial.available()) {
    // 读取一个字节的数据
    Voice_Control = mySerial.read();

    // 将接收到的数据通过硬件串口输出，便于调试和监控
    Serial.println(Voice_Control);
  }

  //判断是否是播报时间的指令码
  if (Voice_Control == 31) {
    Uart_SendCmd(18, hour, min);
  }
  Voice_Control = 0;
}