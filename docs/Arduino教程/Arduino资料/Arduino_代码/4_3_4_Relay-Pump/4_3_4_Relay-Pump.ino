/*
 * 文件名 : Relay-Pump
 * 功能   : 让继电器控制水泵抽水模拟抽水系统
 * 编译IDE：ARDUINO 2.3.6
 * 作者   : https://www.keyesrobot.cn/
*/

const int RelayPin = 25; //定义继电器引脚为IO25

char content;  //定义一个字符串，用于存储串口接收到的值

void setup() {
  Serial.begin(9600);
  pinMode(RelayPin,OUTPUT); //定义引脚IO25为输出模式
}

void loop() {
  //arduino串口方法Serial.read() 每次只接收一个字节
  //当键盘输入aaa时，每次只接收一个a，共接收三次
  if(Serial.available() > 0) {
    if (Serial.read() == 'a') //当输入的值等于a时，执行灌溉任务
    {
      digitalWrite(RelayPin,HIGH);
      delay(400);//灌溉的延时，请设置100~400之间
      digitalWrite(RelayPin,LOW);
      delay(700);
    }
  }
}
