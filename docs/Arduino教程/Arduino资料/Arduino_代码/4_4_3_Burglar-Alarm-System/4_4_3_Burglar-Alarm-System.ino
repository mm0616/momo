/*
 * 文件名 : Burglar-Alarm-System
 * 功能   : 结合智能语音模块、LED模块和无源蜂鸣器模拟防盗警报系统
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

//导入相关库文件
#include <SoftwareSerial.h>

// 定义引脚常量
const int RX_PIN = 23; // 引脚 GPIO23 为 RX
const int TX_PIN = 5; // 引脚 GPIO5 为 TX
const int buzzerPin = 16;        //蜂鸣器模块连接引脚为16
const int ledPin = 27;       // 定义LED的GPIO引脚为27

SoftwareSerial mySerial(RX_PIN, TX_PIN); // 定义软件串口引脚（RX, TX）

void setup() {
  Serial.begin(9600); // 硬件串口（与电脑通信）
  mySerial.begin(9600); // 软件串口（与外设通信）
  //设置引脚的模式
  pinMode(buzzerPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  if (mySerial.available()) { // 接收语音控制模块的外设数据
    int command = mySerial.read(); // 将接收到的外设数据进行赋值 
    if(command == 21){
      digitalWrite(ledPin,HIGH);
      //警报声
      for(int i = 200; i<=1000; i+=10){ 
        tone(buzzerPin,i);
        delay(10);
      }
    }
    else if(command == 22){
      noTone(buzzerPin);
      digitalWrite(ledPin,LOW);
    }
    mySerial.println(command);
    Serial.println(command);
  }  
}
