#include "headfile.h"

//编码器初始化//
void Encoder_Init(void)
{
  ftm_count_init(ftm0);      //对E0引脚输入的脉冲进行计算   E0接编码器LSB
  gpio_init(E1,GPI,0);       //用于判断方向                 E1接编码器DIR
  port_pull(E0);
  port_pull(E1);             //IO上拉
  
  ftm_count_init(ftm1);      //对E7引脚输入的脉冲进行计数   E7接编码器LSB
  gpio_init(H5,GPI,0);       //用于判断方向                 H5接编码器DIR
  port_pull(E7);
  port_pull(H5);
}

//编码器滤波输出//

float Encoder_Get(FTMn ftmn)
{
  float a=0.0;    //滤波权重
  uint16 temp;
  float Pulse;
  static float LastPulse=0.0;
  
  temp = ftm_count_get(ftmn);     //脉冲读取
  Pulse = a*LastPulse+(1-a)*temp;    //一阶低通滤波  
  LastPulse = Pulse;
  ftm_count_clean(ftmn);    //计数器清零
  return Pulse;
}
