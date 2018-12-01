#include "headfile.h"

//��������ʼ��//
void Encoder_Init(void)
{
  ftm_count_init(ftm0);      //��E0���������������м���   E0�ӱ�����LSB
  gpio_init(E1,GPI,0);       //�����жϷ���                 E1�ӱ�����DIR
  port_pull(E0);
  port_pull(E1);             //IO����
  
  ftm_count_init(ftm1);      //��E7���������������м���   E7�ӱ�����LSB
  gpio_init(H5,GPI,0);       //�����жϷ���                 H5�ӱ�����DIR
  port_pull(E7);
  port_pull(H5);
}

//�������˲����//

float Encoder_Get(FTMn ftmn)
{
  float a=0.0;    //�˲�Ȩ��
  uint16 temp;
  float Pulse;
  static float LastPulse=0.0;
  
  temp = ftm_count_get(ftmn);     //�����ȡ
  Pulse = a*LastPulse+(1-a)*temp;    //һ�׵�ͨ�˲�  
  LastPulse = Pulse;
  ftm_count_clean(ftmn);    //����������
  return Pulse;
}
