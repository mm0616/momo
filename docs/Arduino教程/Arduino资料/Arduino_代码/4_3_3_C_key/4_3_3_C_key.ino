/*
 * 文件名 : C_key
 * 功能   : 让无源蜂鸣器播放C调的Do，Re，Mi，Fa，So，La，Si
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

const int Buzzer_Pine = 16; //定义喇叭引脚为IO16

void setup() {
  pinMode(Buzzer_Pine, OUTPUT);//定义引脚IO16为输出模式
}

void loop() {
  tone(Buzzer_Pine, 262); //低DO播放500ms
  delay(500);
  tone(Buzzer_Pine, 294); //低Re播放500ms
  delay(500);
  tone(Buzzer_Pine, 330); //低Mi播放500ms
  delay(500);
  tone(Buzzer_Pine, 349); //低Fa播放500ms
  delay(500);
  tone(Buzzer_Pine, 392); //低So播放500ms
  delay(500);
  tone(Buzzer_Pine, 440); //低La播放500ms
  delay(500);
  tone(Buzzer_Pine, 494); //低Si播放500ms
  delay(500);
  noTone(Buzzer_Pine); //停止播放一秒
  delay(1000);
}