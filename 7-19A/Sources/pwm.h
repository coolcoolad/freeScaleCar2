//[PWM.h]PWM处理函数头文件------------------------------------------------*
//功  能:                                                                  *
//    (1)用于声明中断子函数                                                *
//-------------------------------------------------------------------------*
#include <MC9S12XS128.h>    //MCU映像寄存器名

#define MOTOR_OUT_MAX  1900                            //DC电动机频率
#define MOTOR_OUT_MIN -1900
       
void PWMInit(void);
void Motor_No1_forward(unsigned int duty);
void Motor_No2_forward(unsigned int duty);
void Motor_No1_back(unsigned int duty);
void Motor_No2_back(unsigned int duty);
