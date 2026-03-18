/*
 * 文件名 : WiFi-HTML-String
 * 功能   : WiFi网页显示字符串!
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

// 初始化LCD模块
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*替换为您的网络凭据（输入您自己的WiFi名称和密码）*/
const char* ssid = "REPLACE_WITH_YOUR_SSID";  // 输入你自己的WiFi名称
const char* password = "REPLACE_WITH_YOUR_PASSWORD"; // 输入你自己的WiFi密码

WebServer server(80); //设置网页端口为80，可以直接输入IP地址进入网页，不需要输入端口号

// 网页初始化
void handleRoot() {
  // 用于向客户端发送HTTP响应,发送200表示成功
  server.send(200, "text/html", "<h1>Hello, World!</h1>");
}

void setup() {
  Serial.begin(9600);
  // wifi初始化
  WiFi.begin(ssid, password);
  // 寻找wifi，未连接成功，则一直处于连接中状态，while循环
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // 连接成功，打印 IP 地址
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // 初始化LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IP:");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  server.on("/", handleRoot);
  // 启动服务器
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}