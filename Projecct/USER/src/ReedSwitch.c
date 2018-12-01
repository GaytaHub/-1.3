#include "headfile.h"

void ReedSwitch_Init(void)
{
  gpio_init(H2,GPI,1);   
  port_pull(H2);  
}

//�ɻɹܿ��ؼ��
int ReedSwitch_Read(void)
{
  return !gpio_get(H2);    //�պ�Ϊ0
}

//�յ��߼��
extern float BasicSpeed;
extern struct Data DifSpeed_P;

uint16 EndLine_Count = 50;
int End = OFF;

void EndLine_Scan(void)
{
  if(EndLine_Count > 0)       //�յ��߷�����ʱ���
  {
    EndLine_Count--;
    systick_delay_ms(25);
  }
  if(EndLine_Count <= 0)    
  {
    End = ReedSwitch_Read(); 
    if(End == ON)
    {
      End = ReedSwitch_Read();
      if(End == ON) 
        End = ON;
    }
  }  
  if(End == ON)       //�յ���ͣ������
  {
    BasicSpeed = 0;
    DifSpeed_P.Value = 5;
  }
}
