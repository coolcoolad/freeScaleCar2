//[PWM.h]PWM������ͷ�ļ�------------------------------------------------*
//��  ��:                                                                  *
//    (1)���������ж��Ӻ���                                                *
//-------------------------------------------------------------------------*
#include <MC9S12XS128.h>    //MCUӳ��Ĵ�����

#define MOTOR_OUT_MAX  1900                            //DC�綯��Ƶ��
#define MOTOR_OUT_MIN -1900
       
void PWMInit(void);
void Motor_No1_forward(unsigned int duty);
void Motor_No2_forward(unsigned int duty);
void Motor_No1_back(unsigned int duty);
void Motor_No2_back(unsigned int duty);
