#include "headfile.h"

//电感数据归一化  结果：归一化值
extern float Inductor[InductorsNum];
extern float MaxValue[InductorsNum];
extern float MinValue[InductorsNum];
void Inductors_Read(void);

#define Max_Min         //Max-Min或Max-0  //归一化方式选择，可屏蔽
#define NormalRange 100       //归一化范围
#define Multiple 100         //放大倍数
float NormalValue[InductorsNum];
float TotalOffset;
int Stop = OFF;   //停车标志

void Inductor_DataProcess(void)
{
  uint8 i;
  float Offset[2];
  
  Inductors_Read();
  for(i=0;i<InductorsNum;i++)
  {
#ifdef Max_Min
    NormalValue[i] = NormalRange * (Inductor[i] - MinValue[i]) / (MaxValue[i] - MinValue[i]);
#else
    NormalValue[i] = NormalRange * Inductor[i] / MaxValue[i];
#endif
  }
  //停车判断
  if(NormalValue[0] < 10 && NormalValue[1] < 10 && NormalValue[2] < 10)
    Stop = ON;
  Offset[0] = Multiple * (NormalValue[0] - NormalValue[2]) / (NormalValue[0] + NormalValue[2]);
  Offset[1] = Multiple * (NormalValue[3] - NormalValue[4]) / (NormalValue[3] + NormalValue[4]);
  TotalOffset =  Offset[0] + Offset[1];
}


//编码器脉冲转为轮胎线速度（单位cm/s，标量）
float Encoder_Get(FTMn ftmn);

#define Standard 5578   //1m距离编码器输出脉冲数

float Wheel_Speed(FTMn ftmn)
{
  float Pulse,WheelSpeed;

  Pulse = Encoder_Get(ftmn);
  WheelSpeed = (Pulse*100.0)/(Standard*InterruptTime)*1000.0;  //速度换算   
  return WheelSpeed;
}  
//轮子实际速度（单位cm/s，矢量）
float LeftWheel,RightWheel;

void Wheel_Direction(void)
{
  if(gpio_get(E1))    LeftWheel = Wheel_Speed(ftm0);
  else                LeftWheel = -Wheel_Speed(ftm0);
  if(gpio_get(H5))    RightWheel = -Wheel_Speed(ftm1);
  else                RightWheel = Wheel_Speed(ftm1);
}

//动态参数
float Percent;
void Dynamic_Para(void)
{
  float a = 0.50;      //滤波系数
  static float LastPercent;
  
  Percent = 1 - myabs(TotalOffset  / (2 * Multiple));
  Percent = Percent * (1 - a) + LastPercent * a;
  LastPercent = Percent;
//  if(Percent <= 0.8)
//    Percent = 0.8;
}

//数据整合
extern struct Data Offset_D;
float Offset_PID(float Offset);
float Speed_PID(float SetValue,float RealValue);
float DifSpeed_PID(float SetValue,float RealValue);

//设定值参数
float BasicSpeed = 0;
float SetSpeed;       //设定速度
float RealSpeed;      //实际速度
float SpeedOut;       //速度闭环输出
float SetDifSpeed;      //设定差速  由上一级偏差闭环输出得到
float RealDiffSpeed;  //实际差速
float DifSpeedOut;    //差速闭环输出

void Data_Result(void)
{
  //数据获取
  Inductor_DataProcess();
  Wheel_Direction();
  
  Dynamic_Para();
  SetSpeed = BasicSpeed * Percent* Percent;
  RealSpeed = (LeftWheel + RightWheel)/2.0;
  SetDifSpeed = Offset_PID(TotalOffset);
  RealDiffSpeed = RightWheel - LeftWheel;
  
//#define PID_Debug 
#ifdef PID_Debug
  SetSpeed = 280;
  SetDifSpeed = 0;
#endif
  SpeedOut = Speed_PID(SetSpeed,RealSpeed);
  DifSpeedOut = DifSpeed_PID(SetDifSpeed,RealDiffSpeed);
}
