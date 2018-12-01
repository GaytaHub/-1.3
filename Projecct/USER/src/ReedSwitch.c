#include "headfile.h"

void ReedSwitch_Init(void)
{
  gpio_init(H2,GPI,1);   
  port_pull(H2);  
}

//干簧管开关检测
int ReedSwitch_Read(void)
{
  return !gpio_get(H2);    //闭合为0
}

//终点线检测
extern float BasicSpeed;
extern struct Data DifSpeed_P;

uint16 EndLine_Count = 50;
int End = OFF;

void EndLine_Scan(void)
{
  if(EndLine_Count > 0)       //终点线发车延时检测
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
  if(End == ON)       //终点线停车处理
  {
    BasicSpeed = 0;
    DifSpeed_P.Value = 5;
  }
}
