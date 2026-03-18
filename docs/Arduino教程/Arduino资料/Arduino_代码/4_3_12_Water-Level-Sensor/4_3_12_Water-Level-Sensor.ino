/*
 * 文件名 : Water-Level-Sensor
 * 功能   : 读取水位传感器的值
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

const int WaterLevelPin = 33; //定义水位传感器引脚为33

void setup() {

  Serial.begin(9600); //初始化串口
  pinMode(WaterLevelPin,INPUT); //设置水位传感器引脚为输入模式
}

void loop() {
  //读取水位传感器的值，并且定义一个变量用来存储土水位传感器的值
  int ReadValue = analogRead(WaterLevelPin);
  Serial.print("WaterLevel Value: ");
  Serial.println(ReadValue);
  delay(500);
}
