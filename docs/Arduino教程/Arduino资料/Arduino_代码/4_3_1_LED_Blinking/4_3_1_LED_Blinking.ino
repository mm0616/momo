/*
 * 文件名 : LED_Blinking
 * 功能   : 让led灯闪烁.
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn
*/

const int LED_Pin = 27; //定义LED的GPIO引脚

void setup() {
// 初始化数字引脚LED_Pin作为输出模式。
  pinMode(LED_Pin, OUTPUT);
}

void loop() {
  digitalWrite(LED_Pin, HIGH);  // 打开LED （HIGH是高电平）
  delay(1000);                  // 等待1秒
  digitalWrite(LED_Pin, LOW);   // 通过使电压低来关闭LED
  delay(1000);                  //等待1秒
}