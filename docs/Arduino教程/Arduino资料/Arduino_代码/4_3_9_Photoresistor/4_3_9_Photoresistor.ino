/*
 * 文件名 : Photoresistor
 * 功能   : 读取光敏传感器的值
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

const int Photoresistor_Pin = 34;   //光敏电阻的引脚定义为GPIO34

void setup() {
  //初始化串口
  Serial.begin(9600);
  //设置光敏引脚为输入模式
  pinMode(Photoresistor_Pin,INPUT);
}

void loop() {
  //读取光敏传感器的值
  int ReadValue = analogRead(Photoresistor_Pin);
  //打印值，注意：ESP32开发板是12-bit的ADC，读取到的值范围：0~4095
  Serial.print("Photoresistor value: ");
  Serial.println(ReadValue);
  delay(500);
}
