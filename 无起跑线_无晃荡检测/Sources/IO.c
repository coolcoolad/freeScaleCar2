
//IO.c
#include "NeededHeadFile.h"

void IOinit()
{                           //1输出 0输入
  DDRA=0b10101010;            //PA0 PA2 PA4 PA6  拨码开关输入控制 
  DDRB=0b10001111;            //PB0和PB1用于电机使能
  PORTB_PB7 = 0;            //CCD激活补光灯
  
  DDRT_DDRT0 = 1;             //PT0口设为普通输出口
  PTT_PTT0 = 0;               //初值为0
//  DDR1AD0_DDR1AD04 = 1;       //AD4口设为普通输出口，用于输出高低电平
//  PT1AD0_PT1AD04=0;           //初值为0
//  DDR1AD0_DDR1AD05 = 1;       //AD5口设为普通输出口，用于输出高低电平
//  PT1AD0_PT1AD05=0;           //初值为0
}