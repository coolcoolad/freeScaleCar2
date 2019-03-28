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

///////////////角度控制参数//////////////////
u8 Pangle=220,Dangle=17;         
u8 carBalanceAngle=200; 
#define Zmax 495
#define Zmin 169
s16 Zcenter = 276/*275 278 308*/,Gcenter = 419;
float tg = 1.0;
float Rz = (180.0/(Zmax-Zmin)),Rg = 1.00;
///////////////方向控制参数//////////////////
u8 Pdirection=75,Ddirection=10;
u8 PixelCenter=60;
u8 ThresholdOffset =10,PixelOffset=6;
s16 Rcenter = 298;
u8 CCDcount=0;  
u16 gPixel[128] = {0};
///////////////速度控制参数//////////////////
u8 Pspeed=30,Dspeed=2;
u8 UniformSpeed = 160;
u8 WanDaoJianSu = 20;               
s16 Ycenter = 298;
float UNIFORM_SPEED=0;
u8 SpeedCount=0;
///////////////其他参数//////////////////////
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
  SetBusCLK_64M();      //64M主线频率
	ADCInit();           //初始化ADC口
	SCI_Init();           //初始化SCI串口
	IOinit();              //IO口初始化
	PWMInit();           //初始化PWM输出口
 	PA_init();            //初始化脉冲累加器
  ECT1_INIT();        //通道1为输入捕捉
  PIT_Init();          //周期中断PIT初始化
  DisableInterrupts;
	Dly_ms(1000);
	GetGcenterRcenter();
	/*-----------------------------------*/
	while(1)
	{
	  if(PORTA == 0b01010100)//打开拨码开关，输出待输出数据 
      ShowWave();
	  
    if(PORTA == 0b01010000)//打开拨码开关，进行参数接受  
    { 
      DisableInterrupts;      
      PWMDTY01 = 0;
      PWMDTY23 = 0;        
      PWMDTY45 = 0;
      PWMDTY67 = 0;  //电机停止
      receivePara();
      EnableInterrupts;
    }
    if(PORTA == 0b01010001 || PORTA == 0b01000001)
      OutputPixel(); //大概花费12ms
    Dly_ms(10);
    
    EnableInterrupts;
    //电机死区测试
   // Motor_No1_forward(900);
   // Motor_No2_forward(900);
 	}
}

/*-----------------PIT中断服务程序------------------*/ 
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt 66 PIT_ISR1(void)//PIT0 5毫秒周期中断服务程序，用于数据采集，车体控制                        
{    
  //DisableInterrupts;
  if(PITTF_PTF0==1)
  { 
    PITTF_PTF0=1;               //清中断标志位
     
    if(PTT_PTT0 == 0) //利用输出波的频率测算执行时间
      PTT_PTT0 = 1;
    else
      PTT_PTT0 = 0;
      
    if(StartCount >= 0)    //起跑延时2秒
      StartCount--;
    if(StartCount == -1)
    {
      //UNIFORM_SPEED = UniformSpeed*2;
      //DirectionSpeedControlFlag = 1;
      if(StartSpeedUpTimer == 0) //起始缓慢加速
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
    
    GetZangleGangle();          //每10ms调整车体姿势，获取角度
    GetAngleControlValue();      //获取PWM角度控制量

    CCDcount++;
    if(CCDcount == 2)
    {
      TSL1401_GetLine(gPixel);    //每20ms更新像素值，花费4ms 
      GetYsubYaddDIRangle(gPixel);
      CCDcount=0;
    }
    
    SpeedCount++;
    if(SpeedCount == 10)
    {       
      GetNewSpeedOldSpeed();    //每100ms调节车速
      SpeedCount=0;
    }
    
    GetMotorPlus();
    GetDirectionControlValue(CCDcount);
    GetSpeedControlValue(SpeedCount);  
      
  	MotorPWMOut();	          //把综合后的PWM量输出给电机
   }
   //EnableInterrupts;	
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //定时器中断，输入捕捉
void interrupt 9 Catch(void)
{
  if(TFLG1_C1F == 1)
  {
    TFLG1_C1F=1;//清除标志位
    BianMaQiCount2++;
  }
}
 
#pragma  CODE_SEG DEFAULT