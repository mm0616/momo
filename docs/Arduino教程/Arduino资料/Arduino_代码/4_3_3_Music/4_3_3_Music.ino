/*
 * 文件名 : Music
 * 功能   : 让无源蜂鸣器播放音乐.
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/
int beeppin = 16;  //定义无源蜂鸣器引脚为IO16

// do、re、mi、fa、so、la、si
int doremi[] = { 262, 294, 330, 370, 392, 440, 494,                                                        //低音调0-6
                 523, 587, 659, 698, 784, 880, 988,                                                        //中音调7-13
                 1047, 1175, 1319, 1397, 1568, 1760, 1967 };                                               //高音调14-20
int happybirthday[] = { 5, 5, 6, 5, 8, 7, 5, 5, 6, 5, 9, 8, 5, 5, 12, 10, 8, 7, 6, 11, 11, 10, 8, 9, 8 };  // 根据简谱低中高音找到doremi[]数组中的位置号
int meter[] = { 1, 1, 2, 2, 2, 4, 1, 1, 2, 2, 2, 4, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 4 };               // 节拍

void setup() {
  pinMode(beeppin, OUTPUT);  //定义引脚IO16为输出模式
}

void loop() {
  for (int i = 0; i <= 24; i++) {                 //i<=24 的原因是歌谱中只有24个音调
    tone(beeppin, doremi[happybirthday[i] - 1]);  //用tone()函数发出频率为frequency的波形
    delay(meter[i] * 200);                        //等待1000毫秒
    noTone(beeppin);                              //停止发声
  }
}