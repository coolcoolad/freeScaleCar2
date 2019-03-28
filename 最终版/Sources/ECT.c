#include "ECT.h"
#include <MC9S12XS128.h>

 void 	PA_init(void)
{
  TIOS = 0b01111111;
  PACTL=0X54;	//脉冲累加器使能，事件计数模式，上升沿增加计数，
 		        //输入时钟为PACLK，脉冲累加中断使能,脉冲累加输入中断禁止 
  PACNT=0x0000;	//清零
   
}

void ECT1_INIT()       //输入捕捉通道1初始化函数
{
 TSCR2=0x00;           //关闭溢出中断且1分频
 TIE=0;               //通道1中断关闭
 TIOS_IOS1 = 0;          //定通道1为输入捕捉
 TCTL4=0x04;
 TFLG1=0x02;   //1对应标志位清零
 TIE=0x02;               //通道1中断使能 
 TSCR1=0x80;      //开启总定时器中断
}
  




