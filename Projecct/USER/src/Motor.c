#include "headfile.h"

//电机初始化//
void Motor_Init(void)
{
  ftm_pwm_init(ftm2,ftm_ch2,15000,0); 
  ftm_pwm_init(ftm2,ftm_ch3,15000,0);
  ftm_pwm_init(ftm2,ftm_ch4,15000,0);
  ftm_pwm_init(ftm2,ftm_ch5,15000,0);
}

