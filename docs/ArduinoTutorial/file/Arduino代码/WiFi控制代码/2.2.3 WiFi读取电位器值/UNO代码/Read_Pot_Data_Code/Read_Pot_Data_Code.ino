// 定义电位器连接的引脚号
int PotPin = A1;

// 用于存储从串口接收到的控制指令字符串
String WiFi_Control = "";

void setup() {
  // 初始化串口通信，波特率设置为750（注意：非标准波特率，需确保通信双方一致）
  Serial.begin(750);

  // 将电位器引脚设置为输入模式
  pinMode(PotPin, INPUT);
}

void loop() {
  //读取传感器数据
  int PotValue = analogRead(PotPin);

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

  // 判断接收到的指令内容是否是发送数据指令"SENSOR_READ"
  if (WiFi_Control == "SENSOR_READ") {
    //请注意串口发送的数据格式为 “名称:数据”，如电位器的值是1000就是“POT:1000”
    Serial.println("POT:" + String(PotValue));
  }
  // 清除指令字符串，避免重复执行
  WiFi_Control = "";
}