
//otherFunction.c

#include "NeededHeadFile.h"

void Delay(int k)      //70us
{
  int i,j;
  for (i=0; i<k; i++)
      for (j=0; j<=500; j++);
}

void Dly_ms(int ms) 
{ 
    int ii;
    int jj; 
    if (ms<1) ms=1; 
    for(ii=0;ii<ms;ii++) 
    for(jj=0;jj<10667;jj++);    //64MHz--1ms   
}

void Error(u8 *str)
{
  PWMDTY01 = 0;       
  PWMDTY23 = 0;        
  PWMDTY45 = 0;
  PWMDTY67 = 0;  //���ֹͣ
  while(1)
    printp("%s\n",str);
}

/********************�趨�ж����ȼ�******************************/
void SetInterruptPriority(void)
{
    INT_CFADDR=0xe0;    //���벶׽�ж�
    INT_CFDATA6=0x07;
    
    INT_CFADDR=0x70;     //�ɼ��ж����ȼ�
    INT_CFDATA4=0x06;
    
    INT_CFADDR=0x70;     //�����ж����ȼ�
    INT_CFDATA5=0x05;   
}
