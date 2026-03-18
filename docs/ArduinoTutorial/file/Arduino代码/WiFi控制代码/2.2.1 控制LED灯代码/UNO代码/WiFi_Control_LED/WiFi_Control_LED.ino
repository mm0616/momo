// 定义LED连接的引脚号（这里是数字引脚3）
int ledPin = 3;

// 用于存储从串口接收到的控制指令字符串
String WiFi_Control = "";

void setup() {
  // 初始化串口通信，波特率设置为750（注意：非标准波特率，需确保通信双方一致）
  Serial.begin(750);

  // 将LED引脚设置为输出模式
  pinMode(ledPin, OUTPUT); 
}

void loop() {
  // 检查串口是否有数据可读
  if (Serial.available()) {
    // 读取直到换行符('\n')的数据，并转换为String类型
    WiFi_Control = Serial.readStringUntil('\n');

    // 去除字符串首尾的空白字符（如回车、空格等）
    WiFi_Control.trim();

    // 将接收到的指令回传到串口，便于调试
    Serial.print("WiFi_Control:");
    Serial.println(WiFi_Control);
  }

  // 判断接收到的指令内容并执行相应操作
  if (WiFi_Control == "RED_LED:1") {
    // 点亮LED（高电平）
    digitalWrite(ledPin, HIGH);
    // 发送应答指令到串口
    Serial.println("ACK:RED_LED:1");

  } else if (WiFi_Control == "RED_LED:0") {
    // 熄灭LED（低电平）
    digitalWrite(ledPin, LOW);
    // 发送应答指令到串口
    Serial.println("ACK:RED_LED:0");
  }
  // 清除指令字符串，避免重复执行
  WiFi_Control = "";  
}