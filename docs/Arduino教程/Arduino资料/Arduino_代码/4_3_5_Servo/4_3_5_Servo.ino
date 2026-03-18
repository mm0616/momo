/*
 * 文件名 : Servo
 * 功能   : 舵机转动
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

#include <ESP32Servo.h>  //需要导入ESP32开发板的舵机库

Servo myservo;  // 创建舵机对象来控制舵机,在ESP32上可以创建16个舵机对象
                
int pos = 0;    // 定义变量存储舵机位置
// ESP32上推荐的PWM GPIO引脚包括2、4、12-19、21-23、25-27、32-33

int servoPin = 26;
                
void setup() {
  myservo.attach(servoPin);   // 将引脚26上的舵机连接到舵机对象上
  myservo.write(180);
  delay(1000);
}

void loop() {
  for (pos = 180; pos >= 80; pos -= 1) { // 从180度到80度
    myservo.write(pos);              // 告诉舵机到变量“pos”的位置
    delay(15);                       // 每次等待15ms让舵机到达对应的位置
  }
  for (pos = 80; pos <= 180; pos += 1) { // 从80度到180度
    // 每次15度
    myservo.write(pos);              //告诉舵机到变量“pos”的位置
    delay(15);                       // 每次等待15ms让舵机到达对应的位置
  }
}