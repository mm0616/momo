/*
 * 文件名 : Soil-Humidity-Sensor
 * 功能   : 读取土壤湿度传感器的值
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

const int SoilHumidityPin = 32; //定义土壤湿度传感器引脚为32

void setup() {
  Serial.begin(9600); //初始化串口
  pinMode(SoilHumidityPin,INPUT); //设置土壤湿度传感器引脚为输入模式
}

void loop() {
  //读取土壤湿度传感器的值，并且定义一个变量用来存储土壤湿度传感器的值
  int ReadValue = analogRead(SoilHumidityPin);
  Serial.print("SoilHumidity Value: ");
  Serial.println(ReadValue);
  delay(500);
}
