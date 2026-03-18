/*
 * 文件名 : Steam-Sensor
 * 功能   : 读取水滴传感器的值
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

const int SteamPin = 35;   //定义引脚为35

void setup() {
  Serial.begin(9600); //初始化串口
  pinMode(SteamPin,INPUT); //设置水滴传感器引脚为输入模式
}

void loop() {
  //读取水滴传感器的值
  int ReadValue = analogRead(SteamPin);
  Serial.print("Steam Value: ");
  Serial.println(ReadValue);
  delay(500);
}