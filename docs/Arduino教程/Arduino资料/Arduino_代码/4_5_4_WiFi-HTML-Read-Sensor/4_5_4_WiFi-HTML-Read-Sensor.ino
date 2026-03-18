/*  
 * 名称   : WiFi-HTML-Read-Sensor
 * 功能   : 使用局域网wifi无线读取光照强度值与水量值并显示在网页上
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/ 
*/

#include <WiFi.h>       // 引入WiFi库，控制ESP32的WiFi连接功能
#include <WebServer.h>  // 引入WebServer库，创建HTTP服务器
#include <LiquidCrystal_I2C.h> // 引入LiquidCrystal_I2C库

// 初始化LCD模块
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*替换为您的网络凭据（输入您自己的WiFi名称和密码）*/
const char* ssid = "REPLACE_WITH_YOUR_SSID";  // 输入你自己的WiFi名称
const char* password = "REPLACE_WITH_YOUR_PASSWORD"; // 输入你自己的WiFi密码

WebServer server(80);  // 创建一个Web服务器对象，监听80端口

// 传感器引脚
const int Steam_Pin = 35;   // 定义水滴传感器的引脚GPIO35
const int Light_Pin = 34;  // 光敏传感器接入的引脚GPIO34

void setup() {
  Serial.begin(9600);  // 初始化串口通信，波特率9600
  delay(100);          // 延时100毫秒
  pinMode(Steam_Pin, INPUT); // 设置Steam_Pin引脚为输入模式
  pinMode(Light_Pin, INPUT); // 设置Light_Pin引脚为输入模式

  Serial.println("Connecting to ");
  Serial.println(ssid);  // 打印正在连接的Wi-Fi名称

  // 连接到Wi-Fi网络
  WiFi.begin(ssid, password);

  // 检查Wi-Fi是否连接成功
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");  // 每隔1秒打印一个点，表示正在连接
  }
  Serial.println("");
  delay(500);
  Serial.println("WiFi connected..!");  // Wi-Fi连接成功
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  // 打印分配到的IP地址
  
  // 初始化LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IP:");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  // 设置不同URL路径的处理函数
  server.on("/", handle_OnConnect);    // 根路径，初始化页面
  server.onNotFound(handle_NotFound);  // 处理未找到的路径

  server.begin();                        // 启动Web服务器
  Serial.println("HTTP server started"); // 打印服务器启动信息
}

void loop() {
  server.handleClient();  // 处理客户端请求
}

// 处理根路径请求，显示初始页面
void handle_OnConnect() {
  int lightValue = analogRead(Light_Pin);  // 读取光敏传感器的值
  int steamValue = analogRead(Steam_Pin);  // 读取水滴传感器的值

  String htmlPage = "<!DOCTYPE html><html>\n";
  htmlPage += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  htmlPage += "<title>ESP32 Sensor Data</title>\n";
  htmlPage += "<meta http-equiv=\"refresh\" content=\"1\"> <!-- 自动刷新页面，每5秒刷新一次 -->\n";
  htmlPage += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  htmlPage += "body{margin-top: 50px; background-color: #f4f4f9;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  htmlPage += "p {font-size: 20px;color: #444;margin-bottom: 10px;}\n";
  htmlPage += ".sensor-box { background-color: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1); width: 300px; margin: 20px auto;}\n";
  htmlPage += ".sensor-title { font-size: 24px; font-weight: bold; color: #333; margin-bottom: 10px; }\n";
  htmlPage += ".sensor-value { font-size: 28px; color: #e74c3c; }\n";
  htmlPage += "</style>\n";
  htmlPage += "</head>\n";
  htmlPage += "<body>\n";
  htmlPage += "<h1>ESP32 Sensor Data</h1>\n";

  // 光敏传感器数据显示区
  htmlPage += "<div class=\"sensor-box\">\n";
  htmlPage += "<div class=\"sensor-title\">Light Sensor Value:</div>\n";
  htmlPage += "<div class=\"sensor-value\">" + String(lightValue) + "</div>\n";
  htmlPage += "</div>\n";

  // 水滴传感器数据显示区
  htmlPage += "<div class=\"sensor-box\">\n";
  htmlPage += "<div class=\"sensor-title\">Steam Sensor Value:</div>\n";
  htmlPage += "<div class=\"sensor-value\">" + String(steamValue) + "</div>\n";
  htmlPage += "</div>\n";

  htmlPage += "</body>\n";
  htmlPage += "</html>\n";

  server.send(200, "text/html", htmlPage);  // 返回HTML页面
}

// 处理未找到的路径
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");  // 返回404错误
}
