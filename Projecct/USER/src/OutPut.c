#include "headfile.h"

////������
//�������
void LeftMotor_Out(float PWM)
{
  if(PWM>=0)
  {
  ftm_pwm_duty(ftm2,ftm_ch4,(int16)(PWM)); //���   ��ת ����ռ�ձ�Ϊ ǧ��֮
  ftm_pwm_duty(ftm2,ftm_ch5,0);
  }
  else if(PWM<0)
  {
  ftm_pwm_duty(ftm2,ftm_ch5,-(int16)(PWM));   
  ftm_pwm_duty(ftm2,ftm_ch4,0); 
  }
}
//�ҵ�����
void RightMotor_Out(float PWM)
{ 
  if(PWM>=0)
  {
    ftm_pwm_duty(ftm2,ftm_ch2,(int16)(PWM)); //���   ��ת ����ռ�ձ�Ϊ ǧ��֮
    ftm_pwm_duty(ftm2,ftm_ch3,0);
  }
  else if(PWM<0)
  {
    ftm_pwm_duty(ftm2,ftm_ch3,-(int16)(PWM));   
    ftm_pwm_duty(ftm2,ftm_ch2,0); 
  }
}

//�޷����
extern float SpeedOut;       //�ٶȱջ����
extern float DifSpeedOut;    //���ٱջ����
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


  
  