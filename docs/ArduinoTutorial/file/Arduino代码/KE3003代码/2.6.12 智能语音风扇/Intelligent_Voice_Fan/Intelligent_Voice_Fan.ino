// 引入SoftwareSerial库，用于创建软串口通信（模拟串口，可使用任意数字/模拟引脚）
#include <SoftwareSerial.h>

// 引入SoftPWM库，用于软件模拟PWM输出（适用于不支持硬件PWM的引脚）
#include <SoftPWM.h>

// 创建软串口对象，使用A5作为RX引脚接收数据，A4作为TX引脚发送数据
// 通常用于与语音模块进行串口通信
SoftwareSerial mySerial(A5, A4);

// 定义变量用于存储从语音模块接收到的控制码
volatile int Voice_Control = 0;  // 初始化为0，确保首次判断时不触发任何指令

// 定义直流电机控制引脚
int IN_Pin = A3;  // 电机方向控制引脚
int EN_Pin = A2;  // 电机使能/PWM调速引脚

// 注意：以下setup()中使用了未声明的变量 myservo 和 servoPin，以及未初始化的SoftPWM库
void setup() {
  // 初始化硬件串口，波特率750（非标准值，需确保通信双方一致）
  Serial.begin(750);

  // 初始化软串口，用于与语音模块通信，波特率9600（标准值）
  mySerial.begin(9600);

  //配置模拟PW
  SoftPWMBegin();
  SoftPWMSet(EN_Pin, 0);
  SoftPWMSetFadeTime(EN_Pin, 1000, 1000);
}

void loop() {
  // 持续检查软串口缓冲区是否有来自语音模块的数据
  while (mySerial.available()) {
    // 读取一个字节的数据（通常语音模块发送的是ASCII字符或字节值）
    Voice_Control = mySerial.read();
    // 将接收到的原始数据通过硬件串口打印到串口监视器，便于调试
    Serial.println(Voice_Control);
  }

  // 根据接收到的指令值（Voice_Control）执行电机控制
  if (Voice_Control == 19) {         // 指令19：最高速正转
    SoftPWMSet(EN_Pin, 255);         // 设置PWM占空比为255（最大速度）
    digitalWrite(IN_Pin, LOW);       // 设置方向引脚为低电平（假设低电平为正转）
  } else if (Voice_Control == 20) {  // 指令20：中低速正转（100/255 ≈ 39%）
    SoftPWMSet(EN_Pin, 100);
    digitalWrite(IN_Pin, LOW);
  } else if (Voice_Control == 21) {  // 指令21：中高速正转（175/255 ≈ 69%）
    SoftPWMSet(EN_Pin, 175);
    digitalWrite(IN_Pin, LOW);
  } else if (Voice_Control == 22) {  // 指令22：最高速正转
    SoftPWMSet(EN_Pin, 255);
    digitalWrite(IN_Pin, LOW);
  } else if (Voice_Control == 23) {  // 指令23：停止（PWM设为0）
    SoftPWMSet(EN_Pin, 0);
    digitalWrite(IN_Pin, LOW);
  }

  // 清除指令字符串，避免重复执行
  Voice_Control = 0;
}