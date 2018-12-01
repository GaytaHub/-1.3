#include "headfile.h"

////待测试
//左电机输出
void LeftMotor_Out(float PWM)
{
  if(PWM>=0)
  {
  ftm_pwm_duty(ftm2,ftm_ch4,(int16)(PWM)); //电机   正转 设置占空比为 千分之
  ftm_pwm_duty(ftm2,ftm_ch5,0);
  }
  else if(PWM<0)
  {
  ftm_pwm_duty(ftm2,ftm_ch5,-(int16)(PWM));   
  ftm_pwm_duty(ftm2,ftm_ch4,0); 
  }
}
//右电机输出
void RightMotor_Out(float PWM)
{ 
  if(PWM>=0)
  {
    ftm_pwm_duty(ftm2,ftm_ch2,(int16)(PWM)); //电机   正转 设置占空比为 千分之
    ftm_pwm_duty(ftm2,ftm_ch3,0);
  }
  else if(PWM<0)
  {
    ftm_pwm_duty(ftm2,ftm_ch3,-(int16)(PWM));   
    ftm_pwm_duty(ftm2,ftm_ch2,0); 
  }
}

//限幅输出
extern float SpeedOut;       //速度闭环输出
extern float DifSpeedOut;    //差速闭环输出
extern int Stop;

float LeftOut,RightOut;
struct Data Motor_MaxOut = {9900,50};
struct Data Motor_MinOut = {-8000,50};

void Motor_OutPut(void)
{
  LeftOut = SpeedOut - DifSpeedOut;
  RightOut = SpeedOut + DifSpeedOut;
//#define Motor_Debug
#ifdef Motor_Debug
  LeftOut = 3000;
  RightOut = 3000;
#endif
  LeftOut = limit_ab(LeftOut,Motor_MaxOut.Value,Motor_MinOut.Value);
  RightOut = limit_ab(RightOut,Motor_MaxOut.Value,Motor_MinOut.Value);
  if(Stop == ON)
  {
    LeftOut = 0;
    RightOut = 0;
  }
    LeftMotor_Out(LeftOut);
    RightMotor_Out(RightOut);
}


  
  