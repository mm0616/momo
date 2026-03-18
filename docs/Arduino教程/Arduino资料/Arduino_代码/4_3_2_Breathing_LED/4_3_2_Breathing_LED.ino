/*
 * 文件名 : Breathing_LED
 * 功能   : 让led灯像呼吸一样忽明忽暗.
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

const int ledPin = 27;  // 定义LED的GPIO引脚

void setup() {
  pinMode(ledPin, OUTPUT); //设置LED引脚为输出模式。
}

void loop() {
  for (int i = 0; i < 255; i++) { //使LED逐渐亮
    analogWrite(ledPin, i); //输出PWM
    delay(10);
  }
  for (int i = 255; i > -1; i--) {  //使LED逐渐熄灭
    analogWrite(ledPin, i); //输出PWM
    delay(10);
  }
}