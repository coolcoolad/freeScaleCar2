//[ADC.h]ADת��-------------------------------------------------------------
#ifndef  ADC_H    //�����ظ�����
#define  ADC_H
//ADת����Ҫ�õ���ͷ�ļ�
#include <MC9S12XS128.h>    //MCUӳ��Ĵ����� 

//����ͨ����غ�������
void   ADCInit(void);                    //A/Dת����ʼ��
void get_ADvalue(unsigned int *AD_value);    //��·A/Dת��
unsigned int ADCValue(unsigned char channel);


extern unsigned int AD_value[8];
                                        
#endif
