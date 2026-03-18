#ifndef JX_UART_SEND_H_
#define JX_UART_SEND_H_

#ifdef __cplusplus
extern "C" {
#endif

// 串口发送消息最大长度
#define UART_SEND_MAX      32
#define UART_MSG_HEAD_LEN  2
#define UART_MSG_FOOT_LEN  2

// 串口发送消息号
#define U_MSG_Light_value2      1
#define U_MSG_Temp_value1      2
#define U_MSG_Hum_value1      3
#define U_MSG_Uitra_val1      4
#define U_MSG_Smoke_value1      5
#define U_MSG_Alcohol_value1      6
#define U_MSG_Soil_value1      7
#define U_MSG_impack_call      8
#define U_MSG_tepm_call      9
#define U_MSG_titl_call      10
#define U_MSG_smoke_call      11
#define U_MSG_distance_call      12
#define U_MSG_alcohol_call      13
#define U_MSG_pir_call      14
#define U_MSG_vibration_call      15
#define U_MSG_rain_call      16
#define U_MSG_soil_call      17
#define U_MSG_time_call      18

// 串口消息参数类型
typedef union {
  double d_double;
  int d_int;
  unsigned char d_ucs[8];
  char d_char;
  unsigned char d_uchar;
  unsigned long d_long;
  short d_short;
  float d_float;
}uart_param_t;

// 十六位整数转32位整数
void _int16_to_int32(uart_param_t* param) {
  if (sizeof(int) >= 4)
    return;
  unsigned long value = param->d_long;
  unsigned long sign = (value >> 15) & 1;
  unsigned long v = value;
  if (sign)
    v = 0xFFFF0000 | value;
  uart_param_t p;
  p.d_long = v;
  param->d_ucs[0] = p.d_ucs[0];
  param->d_ucs[1] = p.d_ucs[1];
  param->d_ucs[2] = p.d_ucs[2];
  param->d_ucs[3] = p.d_ucs[3];
}

// 浮点数转双精度 
void _float_to_double(uart_param_t* param) {
  if (sizeof(int) >= 4)
    return;
  unsigned long value = param->d_long;
  unsigned long sign = value >> 31;
  unsigned long M = value & 0x007FFFFF;
  unsigned long e =  ((value >> 23 ) & 0xFF) - 127 + 1023;
  uart_param_t p0, p1;  
  p1.d_long = ((sign & 1) << 31) | ((e & 0x7FF) << 20) | (M >> 3);
  p0.d_long = (M & 0x7) << 29;
  param->d_ucs[0] = p0.d_ucs[0];
  param->d_ucs[1] = p0.d_ucs[1];
  param->d_ucs[2] = p0.d_ucs[2];
  param->d_ucs[3] = p0.d_ucs[3];
  param->d_ucs[4] = p1.d_ucs[0];
  param->d_ucs[5] = p1.d_ucs[1];
  param->d_ucs[6] = p1.d_ucs[2];
  param->d_ucs[7] = p1.d_ucs[3];
}

// action: Light_value2
void _uart_Light_value2(unsigned char Light_value);

// action: Temp_value1
void _uart_Temp_value1(unsigned char Temp_value);

// action: Hum_value1
void _uart_Hum_value1(unsigned char Hum_value);

// action: Uitra_val1
void _uart_Uitra_val1(unsigned char Uitrasonnic_val);

// action: Smoke_value1
void _uart_Smoke_value1(unsigned char Smoke_value);

// action: Alcohol_value1
void _uart_Alcohol_value1(unsigned char Alcohol_value);

// action: Soil_value1
void _uart_Soil_value1(unsigned char Soil_value);

// action: impack_call
void _uart_impack_call();

// action: tepm_call
void _uart_tepm_call(unsigned char temp_val);

// action: titl_call
void _uart_titl_call();

// action: smoke_call
void _uart_smoke_call();

// action: distance_call
void _uart_distance_call(unsigned char distance_val);

// action: alcohol_call
void _uart_alcohol_call();

// action: pir_call
void _uart_pir_call();

// action: vibration_call
void _uart_vibration_call();

// action: rain_call
void _uart_rain_call();

// action: soil_call
void _uart_soil_call();

// action: time_call
void _uart_time_call(unsigned char H_val, unsigned char M_val);

#ifdef __cplusplus
}
#endif

#endif /*JX_UART_SEND_H_*/

