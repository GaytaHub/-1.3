#include "headfile.h"

//���뿪�س�ʼ��//
void DialSwitch_Init(void)
{
  gpio_init(Switch1,GPI,0);    
  gpio_init(Switch2,GPI,0);
  gpio_init(Switch3,GPI,0);
  gpio_init(Switch4,GPI,0);
}

//���뿪��״̬��ȡ
char DialSwitch_StatusGet(PTX_n ptx_n)
{
  if(gpio_get(ptx_n)) 
    return ON;
  else 
    return OFF;
}