/*
 * 文件名 : Read_Distance
 * 功能   : 读取超声波传感器检测到的距离值
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/
// 定义超声波传感器的引脚
const int trigPin = 14; //trig接GPIO14
const int echoPin = 13; //echo接GPIO13

// 读取传感器数据的功能原型
float readSensorData();

void setup() {
  // 以9600波特率开始串行通信
  Serial.begin(9600);
  // 设置echoPin为输入模式，trigPin为输出模式
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // 打印传感器信息到串行监视器
  Serial.println("Ultrasonic sensor:");  
}

void loop() {
  // 读取超声波传感器的距离值
  float distance = readSensorData();
  // 将测量到的距离打印到串行监视器上
  Serial.print("distance: ");
  Serial.print(distance);   
  Serial.println(" cm");
  // 读数之间的延迟
  delay(100);
}

// 从超声波传感器读取数据的功能
float readSensorData() {
  // 在发送高信号之前触发低信号
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // 给trigPin发送一个10微秒的高信号
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  // 返回低信号
  digitalWrite(trigPin, LOW);
  
  // 测量回声屏上高信号的持续时间
  unsigned long microsecond = pulseIn(echoPin, HIGH);

  // 用声速计算距离（29.00µs / cm）
  float distance = microsecond / 29.00 / 2;

  // 返回计算出的距离
  return distance;
}