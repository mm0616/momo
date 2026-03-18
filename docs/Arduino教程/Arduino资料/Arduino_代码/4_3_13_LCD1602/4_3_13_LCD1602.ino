/*
 * 文件名 : LCD1602
 * 功能   : LCD1602显示字符串等
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

#include <LiquidCrystal_I2C.h>

//初始化LCD1602，其中0x27为I2C地址
//I2C接口:SDA引脚接SDA(IO21), SCL引脚接SCL(IO22)
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  //LCD初始化
  lcd.init();
  // 打开/关闭（可选）背光
  lcd.backlight();
  //lcd.noBacklight();

  //设置位置
  lcd.setCursor(0, 0);
  //显示
  lcd.print("HELLO WORLD 0");
  lcd.setCursor(0, 1);
  lcd.print("HELLO WORLD 1");

  //清空显示
  // lcd.clear();
}

void loop() {

}
