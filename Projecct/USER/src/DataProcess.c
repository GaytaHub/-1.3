#include "headfile.h"

//������ݹ�һ��  �������һ��ֵ
extern float Inductor[InductorsNum];
extern float MaxValue[InductorsNum];
extern float MinValue[InductorsNum];
void Inductors_Read(void);

#define Max_Min         //Max-Min��Max-0  //��һ����ʽѡ�񣬿�����
#define NormalRange 100       //��һ����Χ
#define Multiple 100         //�Ŵ���
float NormalValue[InductorsNum];
float TotalOffset;
int Stop = OFF;   //ͣ����־

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
  //ͣ���ж�
  if(NormalValue[0] < 10 && NormalValue[1] < 10 && NormalValue[2] < 10)
    Stop = ON;
  Offset[0] = Multiple * (NormalValue[0] - NormalValue[2]) / (NormalValue[0] + NormalValue[2]);
  Offset[1] = Multiple * (NormalValue[3] - NormalValue[4]) / (NormalValue[3] + NormalValue[4]);
  TotalOffset =  Offset[0] + Offset[1];
}


//����������תΪ��̥���ٶȣ���λcm/s��������
float Encoder_Get(FTMn ftmn);

#define Standard 5578   //1m������������������

float Wheel_Speed(FTMn ftmn)
{
  float Pulse,WheelSpeed;

  Pulse = Encoder_Get(ftmn);
  WheelSpeed = (Pulse*100.0)/(Standard*InterruptTime)*1000.0;  //�ٶȻ���   
  return WheelSpeed;
}  
//����ʵ���ٶȣ���λcm/s��ʸ����
float LeftWheel,RightWheel;

void Wheel_Direction(void)
{
  if(gpio_get(E1))    LeftWheel = Wheel_Speed(ftm0);
  else                LeftWheel = -Wheel_Speed(ftm0);
  if(gpio_get(H5))    RightWheel = -Wheel_Speed(ftm1);
  else                RightWheel = Wheel_Speed(ftm1);
}

//��̬����
float Percent;
void Dynamic_Para(void)
{
  float a = 0.50;      //�˲�ϵ��
  static float LastPercent;
  
  Percent = 1 - myabs(TotalOffset  / (2 * Multiple));
  Percent = Percent * (1 - a) + LastPercent * a;
  LastPercent = Percent;
//  if(Percent <= 0.8)
//    Percent = 0.8;
}

//��������
extern struct Data Offset_D;
float Offset_PID(float Offset);
float Speed_PID(float SetValue,float RealValue);
float DifSpeed_PID(float SetValue,float RealValue);

//�趨ֵ����
float BasicSpeed = 0;
float SetSpeed;       //�趨�ٶ�
float RealSpeed;      //ʵ���ٶ�
float SpeedOut;       //�ٶȱջ����
float SetDifSpeed;      //�趨����  ����һ��ƫ��ջ�����õ�
float RealDiffSpeed;  //ʵ�ʲ���
float DifSpeedOut;    //���ٱջ����

void Data_Result(void)
{
  //���ݻ�ȡ
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
