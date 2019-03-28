#include <hidef.h>
#include "derivative.h"
#include <MC9S12XS128.h>

#include "receivePara.h"	
#include "allPara.h"
#include "SCI.h"
#include "busClock.h"
#include "otherFunction.h"
#include "IO.h"
#include "Control.h"

///////////////�Ƕȿ��Ʋ���//////////////////
u8 Pangle=220,Dangle=17;         
u8 carBalanceAngle=200; 
#define Zmax 495
#define Zmin 169
s16 Zcenter = 276/*275 278 308*/,Gcenter = 419;
float tg = 1.0;
float Rz = (180.0/(Zmax-Zmin)),Rg = 1.00;
///////////////������Ʋ���//////////////////
u8 Pdirection=75,Ddirection=10;
u8 PixelCenter=60;
u8 ThresholdOffset =10,PixelOffset=6;
s16 Rcenter = 298;
u8 CCDcount=0;  
u16 gPixel[128] = {0};
///////////////�ٶȿ��Ʋ���//////////////////
u8 Pspeed=30,Dspeed=2;
u8 UniformSpeed = 160;
u8 WanDaoJianSu = 20;               
s16 Ycenter = 298;
float UNIFORM_SPEED=0;
u8 SpeedCount=0;
///////////////��������//////////////////////
u8 motorDeadVal = 11;
u8 specialSpeedControl =0;
u8 specialPixelControl = 1;
u8 startLineCheck = 1;
//////////////////////////////////////////
int showWaveData[10];
extern int BianMaQiCount2;
u8 DirectionSpeedControlFlag = 0;
int StartCount=400;
float SpeedSetPart=0;
float PspeedPart=0;
u8 StartSpeedUpTimer=0;
int SpeedUpTimeScale=1;
u8 UniformSpeedBackUp=0;
u8 PspeedTimer=0;
float P_SPEED=0;

void main()
{
  DisableInterrupts; 
  AllParaInit();
  SetBusCLK_64M();      //64M����Ƶ��
	ADCInit();           //��ʼ��ADC��
	SCI_Init();           //��ʼ��SCI����
	IOinit();              //IO�ڳ�ʼ��
	PWMInit();           //��ʼ��PWM�����
 	PA_init();            //��ʼ�������ۼ���
  ECT1_INIT();        //ͨ��1Ϊ���벶׽
  PIT_Init();          //�����ж�PIT��ʼ��
  DisableInterrupts;
	Dly_ms(1000);
	GetGcenterRcenter();
	/*-----------------------------------*/
	while(1)
	{
	  if(PORTA == 0b01010100)//�򿪲��뿪�أ������������� 
      ShowWave();
	  
    if(PORTA == 0b01010000)//�򿪲��뿪�أ����в�������  
    { 
      DisableInterrupts;      
      PWMDTY01 = 0;
      PWMDTY23 = 0;        
      PWMDTY45 = 0;
      PWMDTY67 = 0;  //���ֹͣ
      receivePara();
      EnableInterrupts;
    }
    if(PORTA == 0b01010001 || PORTA == 0b01000001)
      OutputPixel(); //��Ż���12ms
    Dly_ms(10);
    
    EnableInterrupts;
    //�����������
   // Motor_No1_forward(900);
   // Motor_No2_forward(900);
 	}
}

/*-----------------PIT�жϷ������------------------*/ 
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt 66 PIT_ISR1(void)//PIT0 5���������жϷ�������������ݲɼ����������                        
{    
  //DisableInterrupts;
  if(PITTF_PTF0==1)
  { 
    PITTF_PTF0=1;               //���жϱ�־λ
     
    if(PTT_PTT0 == 0) //�����������Ƶ�ʲ���ִ��ʱ��
      PTT_PTT0 = 1;
    else
      PTT_PTT0 = 0;
      
    if(StartCount >= 0)    //������ʱ2��
      StartCount--;
    if(StartCount == -1)
    {
      //UNIFORM_SPEED = UniformSpeed*2;
      //DirectionSpeedControlFlag = 1;
      if(StartSpeedUpTimer == 0) //��ʼ��������
      {
        float temp = UniformSpeed;
       //float temp2 = Pspeed;
        SpeedSetPart = temp*2.0/20.0;
        UNIFORM_SPEED = 0;
        StartSpeedUpTimer++;
        //PspeedPart = temp2/2.0;
        //Pspeed = 0;
      }
      
      if(PspeedTimer == 0)
      {
        float temp = Pspeed;
        P_SPEED = 1.2*temp;
        PspeedTimer++;
      }
    }
    
    GetZangleGangle();          //ÿ10ms�����������ƣ���ȡ�Ƕ�
    GetAngleControlValue();      //��ȡPWM�Ƕȿ�����

    CCDcount++;
    if(CCDcount == 2)
    {
      TSL1401_GetLine(gPixel);    //ÿ20ms��������ֵ������4ms 
      GetYsubYaddDIRangle(gPixel);
      CCDcount=0;
    }
    
    SpeedCount++;
    if(SpeedCount == 10)
    {       
      GetNewSpeedOldSpeed();    //ÿ100ms���ڳ���
      SpeedCount=0;
    }
    
    GetMotorPlus();
    GetDirectionControlValue(CCDcount);
    GetSpeedControlValue(SpeedCount);  
      
  	MotorPWMOut();	          //���ۺϺ��PWM����������
   }
   //EnableInterrupts;	
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //��ʱ���жϣ����벶׽
void interrupt 9 Catch(void)
{
  if(TFLG1_C1F == 1)
  {
    TFLG1_C1F=1;//�����־λ
    BianMaQiCount2++;
  }
}
 
#pragma  CODE_SEG DEFAULT