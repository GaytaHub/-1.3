#include "headfile.h"

//��г�ʼ��
void Inductors_Init(void)
{       
  adc_init(ADC0_SE4);
  adc_init(ADC0_SE5);
  adc_init(ADC0_SE6);		
  adc_init(ADC0_SE7);
  adc_init(ADC0_SE12);
  adc_init(ADC0_SE13);
  adc_init(ADC0_SE14);
  adc_init(ADC0_SE15);
}

//ƽ���˲�
#define times 5    //�ɼ�����

float adc_average(ADCn_Ch adcn_ch)
{
  int value[times],i;
  float Value=0.0;
  for(i = 0;i < times;i++)
  {
    value[i] = adc_once(adcn_ch,ADC_10bit);
    Value += value[i];
  }
  Value = Value/times;
  return Value;
}

//������ݲɼ�
float Inductor[InductorsNum];

void Inductors_Read(void)
{
  Inductor[0] = adc_average(ADC0_SE6);
  Inductor[1] = adc_average(ADC0_SE13);
  Inductor[2] = adc_average(ADC0_SE12);
  Inductor[3] = adc_average(ADC0_SE4);
  Inductor[4] = adc_average(ADC0_SE7);
  Inductor[5] = adc_average(ADC0_SE5);
}

//��������Сֵֵ��ȡ
float MaxValue[InductorsNum] = {0};
float MinValue[InductorsNum] = {4096,4096,4096,4096,4096,4096};

void Inductors_ValueRange_Get(void)
{
  int i;
  Inductors_Read();
  for(i=0;i<InductorsNum;i++)
  {
    if(Inductor[i] > MaxValue[i])
    {
      MaxValue[i] = Inductor[i];
    }           
    if(Inductor[i] < MinValue[i])
    {
      MinValue[i] = Inductor[i];
    }
  }
}

//���ֵ��Χд��flash
#define SECTOR 254
void Inductors_ValueRange_Write(void)
{
  FLASH_Init();
  FLASH_EraseSector(SECTOR);       //��������
  FLASH_WriteSector(SECTOR,(const uint8 *)MaxValue,4*InductorsNum,0);    //��б궨�����ֵд������
  FLASH_WriteSector(SECTOR,(const uint8 *)MinValue,4*InductorsNum,4*InductorsNum);  //��б궨����Сֵд������
}
//���ֵ��Χ��flash��ȡ
#define Max
void Inductors_ValueRange_Read(void)
{
  int i;
  
  FLASH_Init();
  for(i=0;i<InductorsNum;i++)   //��ȡN����еĲ����궨�����ֵ
  {
    MaxValue[i] = flash_read(SECTOR,4*i,float);
    systick_delay_ms(5);
  }
  for(i=0;i<InductorsNum;i++)  //��ȡN����еĲ����궨����Сֵ
  {
    MinValue[i] = flash_read(SECTOR,4*(InductorsNum+i),float);
    systick_delay_ms(5);
  }
}
    