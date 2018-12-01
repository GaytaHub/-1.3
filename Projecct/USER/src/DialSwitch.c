#include "headfile.h"

//拨码开关初始化//
void DialSwitch_Init(void)
{
  gpio_init(Switch1,GPI,0);    
  gpio_init(Switch2,GPI,0);
  gpio_init(Switch3,GPI,0);
  gpio_init(Switch4,GPI,0);
}

//拨码开关状态读取
char DialSwitch_StatusGet(PTX_n ptx_n)
{
  if(gpio_get(ptx_n)) 
    return ON;
  else 
    return OFF;
}