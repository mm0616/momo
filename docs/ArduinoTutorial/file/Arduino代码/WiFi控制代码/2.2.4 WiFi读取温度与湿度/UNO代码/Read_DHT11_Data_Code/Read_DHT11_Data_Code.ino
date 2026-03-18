#include <dht11.h>  //include the library code:
dht11 DHT;
#define DHT11_PIN 3  //定义DHT11为数字口3

// 用于存储从串口接收到的控制指令字符串
String WiFi_Control = "";

void dht11_chk() {
  int chk;
  chk = DHT.read(DHT11_PIN);  // READ DATA
  switch (chk) {
    case DHTLIB_OK:
      break;
    case DHTLIB_ERROR_CHECKSUM:  //校检和错误返回
      break;
    case DHTLIB_ERROR_TIMEOUT:  //超时错误返回
      break;
    default:
      break;
  }
}

void setup() {
  // 初始化串口通信，波特率设置为750（注意：非标准波特率，需确保通信双方一致）
  Serial.begin(750);

  // 将引脚设置为输入模式
  pinMode(DHT11_PIN, INPUT);
}

void loop() {
  //检查DHT11数据是否正常
  dht11_chk();
  //读取传感器数据
  int TempValue = DHT.temperature;
  int HumValue = DHT.humidity;

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
    //请注意串口发送的数据格式为 “名称:数据”，如温度的值是25就是“TEMP:25”
    Serial.println("TEMP:" + String(TempValue));  //发送温度数据给ESP01-S
    Serial.println("HUM:" + String(HumValue));    //发送湿度数据给ESP01-S
  }
  // 清除指令字符串，避免重复执行
  WiFi_Control = "";
}