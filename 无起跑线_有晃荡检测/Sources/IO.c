
//IO.c
#include "NeededHeadFile.h"

void IOinit()
{                           //1��� 0����
  DDRA=0b10101010;            //PA0 PA2 PA4 PA6  ���뿪��������� 
  DDRB=0b10001111;            //PB0��PB1���ڵ��ʹ��
  PORTB_PB7 = 0;            //CCD������
  
  DDRT_DDRT0 = 1;             //PT0����Ϊ��ͨ�����
  PTT_PTT0 = 0;               //��ֵΪ0
//  DDR1AD0_DDR1AD04 = 1;       //AD4����Ϊ��ͨ����ڣ���������ߵ͵�ƽ
//  PT1AD0_PT1AD04=0;           //��ֵΪ0
//  DDR1AD0_DDR1AD05 = 1;       //AD5����Ϊ��ͨ����ڣ���������ߵ͵�ƽ
//  PT1AD0_PT1AD05=0;           //��ֵΪ0
}