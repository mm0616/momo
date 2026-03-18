/*
 * 文件名 : Motor
 * 功能   : 电机（风扇）顺时针逆时针转动
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

const int MotorPin1 = 19;  //(IN+)
const int MotorPin2 = 18;  //(IN-)

void setup() {
  pinMode(MotorPin1,OUTPUT); //设置MotorPin1（IN+）引脚为输出模式
  pinMode(MotorPin2,OUTPUT); //设置MotorPin2（IN-）引脚为输出模式
}

void loop() {
  //逆时针转动2秒
  analogWrite(MotorPin1, 70);
  analogWrite(MotorPin2, 0);
  delay(2000);

  //停止2秒
  //停止的目的:防止正反转的瞬间，电机电流过大，导致开发板供电不足，而被迫复位。
  analogWrite(MotorPin1, 0);
  analogWrite(MotorPin2, 0);
  delay(2000);
  
  //顺时针转动2秒
  analogWrite(MotorPin1, 0);
  analogWrite(MotorPin2, 70);
  delay(2000);
  
  //停止2秒
  analogWrite(MotorPin1, 0);
  analogWrite(MotorPin2, 0);
  delay(2000);
}