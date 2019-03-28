//[ADC.h]AD转换-------------------------------------------------------------
#ifndef  ADC_H    //避免重复定义
#define  ADC_H
//AD转换需要用到的头文件
#include <MC9S12XS128.h>    //MCU映像寄存器名 

//串行通信相关函数声明
void   ADCInit(void);                    //A/D转换初始化
void get_ADvalue(unsigned int *AD_value);    //多路A/D转换
unsigned int ADCValue(unsigned char channel);


extern unsigned int AD_value[8];
                                        
#endif
