/*************************************************/
/*******一次6路连续10位AD采样约为16.67us****************/
/*******5kHZ的波采12点***************************/

#include "ADC.h"
#include "NeededHeadFile.h"

unsigned int AD_value[8];
//--------------------------------------------------------------------------
//ADCInit:A/D转换初始化----------------------------------------------------*
//功  能:初始化AD转换                                                      *
//参  数:无                                                                *
//返  回:无                                                                *
//-------------------------------------------------------------------------*
void ADCInit(void) {
 
 //ATD0CTL0=0X07;      //ATDCTL5的MULT位为1时有效,当完成An7转换后，回到An0 
 ATD0CTL1=0x2f;      //10位精度   8位0x0f  12位0x4f
 ATD0CTL2=0x40;      //AFFC位写1，如果禁止比较功能，读ATDDR则清相应的CCF[n]标志位
                     //关闭外部出发
 ATD0CTL3=0xc0;      //右对 转换序列长度8
 ATD0CTL4=0x02;     //采样时间为4个时钟周期为
                     //ATDCLK=40M/(2*(2+1))=6.67MHZ
 ATD0CTL5=0x30;      // 单次
 ATD0DIEN=0x00;      //模拟输入
}
//--------------------------------------------------------------------------
//AD_Getvalue:8路10位A/D转换函数-------------------------------------------*
//功    能:连续读取8个通道的输出值                                         *
//入口参数:unsigned char *AD_value                                         *
//出口参数:无                                                              *
//-------------------------------------------------------------------------*
void get_ADvalue(unsigned int *AD_value)
{ 
  /*while(!ATD0STAT2_CCF0);//当序列中第1个完成转换，结果放在ATDDR0中，CCF0被置位
                         //以下情况CCFx被清零
                         //写ATDCTL5寄存器，对ETORF标志位手动置1
                         //AFFC=0，读取ATDSTAT1，然后读取ATDDRx
                         //AFFC=1,读取ATDDRx
  *AD_value=ATD0DR0;
  AD_value++;
  
  while(!ATD0STAT2_CCF1);//当序列中第2个完成转换，结果放在ATDDR1中，CCF1被置位
  *AD_value=ATD0DR1;
  AD_value++;

  while(!ATD0STAT2_CCF2);
  *AD_value=ATD0DR2;
  AD_value++;*/
  *AD_value = ADCValue(0);
  AD_value++;
  *AD_value = ADCValue(1);
  AD_value++;
  //*AD_value = ADCValue(2);
  //AD_value++;
}

//---------------------------------------------------------------------
//函 数 名:ADCValue                                                     
//功    能:1路A/D转换函数,获取通道channel的A/D转换结果                  
//参    数:channel = 通道号                                             
//返    回:该通道的12位A/D转换结果                                      
//---------------------------------------------------------------------
unsigned int ADCValue(unsigned char channel)
{
  //暂存A/D转换的结果
  u16 temp;                        
	ATD0CTL5 = channel;
	//取A/D转换结果                                  
  while(!ATD0STAT0_SCF);
  temp = ATD0DR0;
	return  temp;
}


