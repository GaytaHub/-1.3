//#ifndef _PID_h
//#define _PID_h
#include "headfile.h"


//ƫ�����
struct Data Offset_P = {9.0,0.1};
struct Data Offset_DeltaP = {0.09,0.005};
struct Data Offset_D = {95,2};

//�ٶȻ�����
struct Data Speed_P = {40,2};
struct Data Speed_I = {1.3,0.05};//0.80
struct Data Speed_D = {27,2};
struct Data Speed_MaxOut = {9000,500};
struct Data Speed_MinOut = {-1800,500};

//���ٻ�����
struct Data DifSpeed_P = {40,2};
struct Data DifSpeed_I = {0,0};
struct Data DifSpeed_D = {0,2};
struct Data DifSpeed_Max= {300,5};
struct Data DifSpeed_MaxOut = {10000,500};
struct Data DifSpeed_MinOut = {-10000,500};

//�����ٶȲ���
struct Data StrightSpeed = {325,5};


//#endif

