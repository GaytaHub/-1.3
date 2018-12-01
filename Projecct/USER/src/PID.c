#include "headfile.h"

//ƫ��ջ�����//
extern struct Data Offset_P;
extern struct Data Offset_DeltaP;
extern struct Data Offset_D;

float Offset_PID(float Offset)
{
    double temp;
    double p_value,d_value;
    static float LastOffset=0.0;
    float Result;
    
    temp = myabs(Offset);
    p_value = Offset_P.Value * temp + Offset_DeltaP.Value * temp * temp;
    d_value = Offset_D.Value * (Offset - LastOffset);
    LastOffset = Offset;         //ƫ��ֵ����
    if(Offset < 0)
    {
        p_value = -p_value;
    }
    Result = p_value + d_value;
    
    return Result;
}

//�ٶȻ��ջ�����//
//�ٶȻ�����
extern struct Data Speed_P;
extern struct Data Speed_I;
extern struct Data Speed_D;
extern struct Data Speed_MaxOut;
extern struct Data Speed_MinOut;

float Speed_PID(float SetValue,float RealValue)
{
    float index=1.0;
    float NewOffset,AdjustValue;
    static float LastOffset = 0.0;
    static float IntegralGainValue = 0.0;
    
    NewOffset = SetValue - RealValue;
    
    if(myabs(NewOffset)>100)    //����ִ���
    {
        index = 0.0;
    }
    else if(myabs(NewOffset)<20)
    {
        index = 1.0;
        IntegralGainValue += NewOffset;
    }
    else
    {
        index = (100-myabs(NewOffset))/80.0;
        IntegralGainValue += NewOffset;
    }  
    
    AdjustValue = Speed_P.Value * NewOffset + Speed_I.Value * IntegralGainValue * index + Speed_D.Value * (NewOffset - LastOffset);
    LastOffset = NewOffset;
    
    AdjustValue = limit_ab(AdjustValue, Speed_MinOut.Value, Speed_MaxOut.Value);  //�Ե����������޷�
    return AdjustValue;
}


//���ٻ��ջ�//
//���ٻ�����
extern struct Data DifSpeed_P;
extern struct Data DifSpeed_I;
extern struct Data DifSpeed_D;
extern struct Data DifSpeed_Max;
extern struct Data DifSpeed_MaxOut;
extern struct Data DifSpeed_MinOut;

float DifSpeed_PID(float SetValue,float RealValue)
{
    static float LastOffset = 0.0;
    float NewOffset,AdjustValue;
    
    NewOffset = SetValue - RealValue;         
    
    NewOffset = limit(NewOffset, DifSpeed_MaxOut.Value);  //ģ���޻�������
    
    AdjustValue = DifSpeed_P.Value * NewOffset + DifSpeed_D.Value * (NewOffset - LastOffset);
    LastOffset=NewOffset; 
    
    AdjustValue = limit_ab(AdjustValue, DifSpeed_MinOut.Value, DifSpeed_MaxOut.Value);  //�޷����
    return AdjustValue;
}

