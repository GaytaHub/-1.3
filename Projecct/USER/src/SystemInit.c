#include "headfile.h"

//硬件初始化
void  Inductors_Init(void);
void  DialSwitch_Init(void);
void  Encoder_Init(void);
void  Motor_Init(void);
void ReedSwitch_Init(void);

void Hardware_Init(void)
{
  get_clk();              //获取时钟频率 必须执行;
  Inductors_Init();
  DialSwitch_Init();
  Encoder_Init();
  Motor_Init();
  ReedSwitch_Init();
}

//赛道信息采集
void Inductors_Read(void);
void Inductors_ValueRange_Get(void);
void Inductors_ValueRange_Write(void);
void Inductors_ValueRange_Read(void);
char DialSwitch_StatusGet(PTX_n ptx_n);

void Track_Information(void)
{
  if(DialSwitch_StatusGet(Switch4)==ON)
  {
    while(DialSwitch_StatusGet(Switch4)==ON)
    {
      Inductors_Read();
      Inductors_ValueRange_Get();
    }
    Inductors_ValueRange_Write();
  }
  else
  {
    Inductors_ValueRange_Read();
  }
}

//中断初始化
void Interrupt_Init(void)
{
  pit_init_ms(pit0,InterruptTime);	//初始化pit0 		
  set_irq_priority(PIT_CH0_IRQn,1);	//设置pit0优先级
  enable_irq(PIT_CH0_IRQn);	//开启pit0中断
  EnableInterrupts;     //开启总中断
}

//起步初始化,单位：ms
extern float BasicSpeed;
extern struct Data StrightSpeed;

void Speed_Start(int Time_ms)
{
  int SpeedCount;
  static int SpeedStart = ON;
  SpeedCount = (int)(StrightSpeed.Value);
  while(BasicSpeed < StrightSpeed.Value && SpeedStart == ON)
  {
    BasicSpeed++;
    if(Time_ms <= SpeedCount)
      Time_ms = SpeedCount;
    systick_delay_ms((uint16)(Time_ms/SpeedCount));
    if(BasicSpeed >= StrightSpeed.Value)
      SpeedStart = OFF;
  }
}

//软件初始化
void Software_Init(void)
{
  Track_Information();
  systick_delay_ms(600);        //发车前延时
  Interrupt_Init();
  Speed_Start(700);
}
