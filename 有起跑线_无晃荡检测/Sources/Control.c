
//Control.h

#include "ADC.h"
#include "allPara.h"
#include "PWM.h"

#define TSL1401_SI(x)   (PORTB_PB2=(x))
#define TSL1401_CLK(x)  (PORTB_PB3=(x))

#define PixelLimit 70
#define PIXEL_OFFSET 6
#define BALANCE_ANGLE 200
#define PIXEL_CENTER 60

float angleControlValue=0,directionControlValue=0,speedControlValue=0;

float Zangle=0,Gangle=0;
float Gspeed=0;

float Ysub=1,Yadd=1;
float DIRangle=0;
float dirNew=0,dirOld=0;

float fLeftVal=0, fRightVal=0;
float JiFenSpeed=0;
float speedNew=0,speedOld=0;
s16 motorSum1=0,motorSum2=0;//少用s32，易出错
int BianMaQiCount2=0;

float angleSum=0;     //检测晃荡
u8 angleSumCount = 0;
float lastAngleValue=0;
u8 speedDownTimer=0;
float HuangDangJianCeBiLi = 3.0;
float HuangDangJianCe = 14000;
u8 speedDownTimerLimt=15;
float speedPart1=0;

float JiFenY=0;
u8 JiFenYCount=0;
float PoDaoJiaSuBiLi=3.0;
u8 speedUpTimer=0;
u8 speedUpTimerLimt=10;

u8 timerNum=0;  //检测起点
u8 startLineCount=0;
u8 startLineTimer=0;
u8 startLineLimit = 0;
u8 startLineTimer2=0;
int startLineTimer3=0;

u8 ZhangAiCount=0;
float ZhangAiBiLi = 3.0;
u8 speedDownTimer2 = 0;

void AllParaInit()
{
  if(PORTA == 0b00000000)
  {
    Pangle=220;
    Dangle=17;         
    carBalanceAngle=BALANCE_ANGLE; 

    Pdirection=35;
    Ddirection=5;
    PixelCenter=PIXEL_CENTER;
    ThresholdOffset =10;
    PixelOffset=PIXEL_OFFSET;

    Pspeed=30;
    Dspeed=2;
    UniformSpeed = 135;
    WanDaoJianSu = 50;

    motorDeadVal = 11;
    specialSpeedControl = 0;
    specialPixelControl = 1;
    startLineCheck = 1;
  }
  
  if(PORTA == 0b00000001)
  {
    Pangle=220;
    Dangle=17;         
    carBalanceAngle=BALANCE_ANGLE; 

    Pdirection=40;
    Ddirection=7;
    PixelCenter=PIXEL_CENTER;
    ThresholdOffset =10;
    PixelOffset=PIXEL_OFFSET;

    Pspeed=30;
    Dspeed=2;
    UniformSpeed = 140;
    WanDaoJianSu = 50;

    motorDeadVal = 11;
    specialSpeedControl = 0;
    specialPixelControl = 1;
    startLineCheck = 1;
  }
  
  if(PORTA == 0b00000100)
  {
    Pangle=220;
    Dangle=17;         
    carBalanceAngle=BALANCE_ANGLE; 

    Pdirection=75;
    Ddirection=10;
    PixelCenter=PIXEL_CENTER;
    ThresholdOffset =10;
    PixelOffset=PIXEL_OFFSET;

    Pspeed=30;
    Dspeed=2;
    UniformSpeed = 150;
    WanDaoJianSu =80;

    motorDeadVal = 11;
    specialSpeedControl = 0;
    specialPixelControl = 1;
    startLineCheck = 1;
  }
  
  if(PORTA == 0b00000101)
  {
    Pangle=220;
    Dangle=17;         
    carBalanceAngle=BALANCE_ANGLE; 

    Pdirection=109;
    Ddirection=20;
    PixelCenter=PIXEL_CENTER;
    ThresholdOffset =10;
    PixelOffset=PIXEL_OFFSET;

    Pspeed=30;
    Dspeed=2;
    UniformSpeed = 160;
    WanDaoJianSu =20;

    motorDeadVal = 11;
    specialSpeedControl = 0;
    specialPixelControl = 1;
    startLineCheck = 1;
  }
  
  if(PORTA == 0b00010000)
  {
    Pangle=220;
    Dangle=17;         
    carBalanceAngle=BALANCE_ANGLE; 

    Pdirection=35;
    Ddirection=5;
    PixelCenter=PIXEL_CENTER;
    ThresholdOffset =10;
    PixelOffset=PIXEL_OFFSET;

    Pspeed=30;
    Dspeed=2;
    UniformSpeed = 120;
    WanDaoJianSu = 50;

    motorDeadVal = 11;
    specialSpeedControl = 0;
    specialPixelControl = 1;
    startLineCheck = 1;  
   }

  if(PORTA == 0b00010001)
  {
    Pangle=220;
    Dangle=17;         
    carBalanceAngle=BALANCE_ANGLE; 

    Pdirection=40;
    Ddirection=7;
    PixelCenter=PIXEL_CENTER;
    ThresholdOffset =10;
    PixelOffset=PIXEL_OFFSET;

    Pspeed=30;
    Dspeed=2;
    UniformSpeed = 130;
    WanDaoJianSu = 50;

    motorDeadVal = 11;
    specialSpeedControl = 0;
    specialPixelControl = 1;
    startLineCheck = 1;
  }
  
  if(PORTA == 0b00010100)
  {
    Pangle=220;
    Dangle=17;         
    carBalanceAngle=BALANCE_ANGLE; 

    Pdirection=80;
    Ddirection=15;
    PixelCenter=PIXEL_CENTER;
    ThresholdOffset =10;
    PixelOffset=PIXEL_OFFSET;

    Pspeed=30;
    Dspeed=2;
    UniformSpeed = 140;
    WanDaoJianSu = 50;

    motorDeadVal = 11;
    specialSpeedControl = 0;
    specialPixelControl = 1;
    startLineCheck = 1;
  }
  
  if(PORTA == 0b00010101)
  {
   
    Pangle=220;
    Dangle=17;         
    carBalanceAngle=BALANCE_ANGLE; 

    Pdirection=130;
    Ddirection=17;
    PixelCenter=PIXEL_CENTER;
    ThresholdOffset =10;
    PixelOffset=PIXEL_OFFSET;

    Pspeed=30;
    Dspeed=2;
    UniformSpeed = 150;
    WanDaoJianSu = 30;

    motorDeadVal = 11;
    specialSpeedControl = 0;
    specialPixelControl = 1;
    startLineCheck = 1;
  }
  
  if(PORTA == 0b01000000)
  {
    Pangle=220;
    Dangle=17;         
    carBalanceAngle=BALANCE_ANGLE; 

    Pdirection=150;
    Ddirection=19;
    PixelCenter=PIXEL_CENTER;
    ThresholdOffset =10;
    PixelOffset=PIXEL_OFFSET;

    Pspeed=30;
    Dspeed=2;
    UniformSpeed = 180;
    WanDaoJianSu = 30;

    motorDeadVal = 11;
    specialSpeedControl = 0;
    specialPixelControl = 1;
    startLineCheck = 1; 
  }
}

void GetGcenterRcenter()
{
  float num = 10,i=0;
  float sum0,sum1=0,sum2=0,sum4=0;
  
  for(i=0;i < num; i++)//从AD口读取Z轴加速和角速度参数，10次平均
  { 
    sum0 += ADCValue(0);        
    sum1 += ADCValue(1);
    sum2 += ADCValue(2);
    sum4 += ADCValue(4);
  }
  
  Zcenter = (int)(sum0/num);
  Gcenter = (int)(sum1/num);
  Rcenter = (int)(sum2/num);
  Ycenter = (int)(sum4/num);
//  showWaveData[0] = (int)Gcenter;
//  showWaveData[1] = (int)Rcenter;
}

void  GetZangleGangle()
{
  s8 num = 5,i=0;
  s16 sum0=0,sum1=0,sum4=0;
  float temp=0;
  float Yspeed=0;
  
  for(i=0;i < num; i++) {         //从AD口读取Z轴加速和角速度参数，5次平均
    sum0 += ADCValue(0);
    sum1 += ADCValue(1);
    sum4 += ADCValue(4);
  }
  showWaveData[0] = (int)sum0/num;
  
  Zangle = (sum0/num-Zcenter)*Rz;     //通过Z轴比例参数Rz求出Zangle 
	Gspeed = (Gcenter-sum1/num)*Rg;     //通过陀螺仪比例参数Rg求出角速度
  //showWaveData[0] = (int)Gspeed;
  Gspeed += (-Gangle + Zangle)/tg;	    //通过时间常数Tg、Zangle和上次的angle对角速度补偿
  Yspeed = sum4/num-Ycenter;
  
	Gangle += Gspeed*0.010 ;             //对角速度积分：角速度*10毫秒并累加
	if(JiFenYCount < 10)
	{
	  JiFenYCount++;
	  JiFenY += Yspeed*0.010;               //对Y方向加速度进行积分
	}
	else
	{
	  JiFenYCount=0;
	  JiFenY=0;  
	}
	showWaveData[1] = (int)Zangle;
	showWaveData[2] = (int)Gangle;
	
/*	if(Gangle < -55)                //判断车子是否倒下
	{
	   timerNum++;
	   if(timerNum > 20)
	   {
	      PWMDTY01 = 0;
        PWMDTY23 = 0;        
        PWMDTY45 = 0;
        PWMDTY67 = 0;  //电机停止
        while(1);
	   }
	} */
}

void GetAngleControlValue()
{
  float realAngle=0;
  realAngle = Gangle +20.0- carBalanceAngle/10.0;//Gangle + 35 - carBalanceAngle/10.0;       //车体平衡位置偏差+40到+10度		
  angleControlValue = Pangle*5*(realAngle-1.0) + Dangle* Gspeed; 
}

void GetYsubYaddDIRangle(u16 *pixel)
{
  u16 sum=0;
  float temp=0;
  s16 i=0,average=0,threshold=0;
  int count1=0,count2=0;
  u8 blackCount1=0,whiteCount=0,blackCount2=0,startLineFlag=0;
  u8 Max=0,Loc=0;
  float temp1=0;
  
  for(i=0;i < 128;i++)
    sum+=pixel[i];
  average = sum/128;
  threshold = average - ThresholdOffset;
  
  if(threshold < PixelLimit)
    threshold = PixelLimit;
  
  if(PORTA != 0b01000001)
  {
    for(i=0;i < 128;i++)
    {
      if(pixel[i] > threshold)                             
        pixel[i] = 255;
      else
        pixel[i] = 0;
    }
  }
  
  if(StartCount == -1 && startLineTimer3 < 2000)
    startLineTimer3++;
  
  if(startLineCheck == 1 && startLineTimer3 > 1000)
  {
    if(CheckStartLine(pixel) == 1)
    {
      if((startLineTimer == 0 || startLineTimer > 200) && startLineLimit < 1)
        startLineLimit++;
      if((startLineTimer == 0 || startLineTimer > 200) && startLineLimit == 1)
      {
        startLineLimit = 0;
        startLineCount++;
      }
      if(startLineCount >= 1)
        startLineTimer2++;
     }
     if(startLineCount == 1 && startLineTimer < 255)
       startLineTimer++; 
  }
  
  if(startLineTimer2 >= 1 && startLineTimer2 < 50)
    startLineTimer2++;
  
  if(startLineTimer2 >= 50)
  {
     PWMDTY01 = 0;
     PWMDTY23 = 0;        
     PWMDTY45 = 0;
     PWMDTY67 = 0;  //电机停止
     while(1);
  }
   
  count1=PixelCenter;  
  for(i=PixelCenter; i < 118;i++)
    if(pixel[i] == 0)
    {
      count1=i;
      break;
    }
  
  count2=PixelCenter;
  for(i=PixelCenter; i >= 10;i--)
    if(pixel[i] == 0)
    {
      count2=i;
      break;
    } 
  
  if(pixel[PixelCenter] == 0 && ZhangAiCount < 20) //障碍计数
    ZhangAiCount++;
  else
  {
    if(ZhangAiCount > 0)
      ZhangAiCount--;
  }
  
  if(count1 == PixelCenter && count2 != PixelCenter)
    count1 = count2+90;
  if(count1 != PixelCenter && count2 == PixelCenter)
    count2 = count1-90;
  
 if(pixel[PixelCenter]==0 && specialPixelControl == 1)
  {
    count2=PixelCenter;  
    for(i=PixelCenter; i < 118;i++)
      if(pixel[i] == 255)
      {
        count2=i;
        break;
      }
    
    count1=PixelCenter;
    for(i=PixelCenter; i >= 10;i--)
      if(pixel[i] == 255)
      {
        count1=i;
        break;
      }
    
    if(count1 == PixelCenter && count2 != PixelCenter)
      count1 = count2+90;
    if(count1 != PixelCenter && count2 == PixelCenter)
      count2 = count1-90;
    if(count1 == PixelCenter && count2 == PixelCenter)
      ;//障碍
    if(count1 != PixelCenter && count2 != PixelCenter)
    {
      if(128-count2 > count1)
        count1 = count2+90;
      else
        count2 = count1-90;
    }
  } 
  
  Ysub = (count1+count2)/2.0 - PixelCenter;
  Yadd = 100.0;

  temp = 0;
  for(i=0;i < 5;i++)
    temp += ADCValue(2);
  DIRangle = temp/5.0 - Rcenter;

  dirOld = dirNew;
  temp1 = Pdirection;
  dirNew = temp1*200.0*Ysub/Yadd - DIRangle*Ddirection;
  //showWaveData[0] = (int)Ysub;
 // showWaveData[0] = (int)DIRangle;
}

void GetDirectionControlValue(u8 i)
{
  float fValue = dirNew - dirOld;
  directionControlValue = fValue * (i+1)/2.0 + dirOld;
}

int CheckStartLine(u16 *pixel)
{
  u8 i=0,limitCount=0,TransNum=0;
  u16 curPixel = pixel[9];
  for(i=10;i<118;i++)
  {
    while(curPixel == pixel[i])
    {
      limitCount++;
      i++;
    }
    curPixel = pixel[i];
    if(limitCount >= 10) //宽度为10的块
    {
      limitCount=0;
      TransNum++;
    }
  }
  if(TransNum >= 5)
    return 1;
  else
    return 0;
}

void GetMotorPlus()
{
  u16 temp = PACNT;
  int BianMaQiCount1=0;
  BianMaQiCount1=temp;
 // int BianMaQiCount2=0;
 // BianMaQiCount2 = BianMaQiCount1+(int)(DIRangle/10.0);
  PACNT = 0;
  if(BianMaQiCount1 > 255)
    BianMaQiCount1 = 200;
  else if(BianMaQiCount1 < 0)
    BianMaQiCount1 = 20;
 // showWaveData[2] = (int)BianMaQiCount1;
 // showWaveData[3] = (int)BianMaQiCount2;
  if(fLeftVal > 0)
    BianMaQiCount1 = -BianMaQiCount1;
  if(fRightVal > 0)
    BianMaQiCount2 = -BianMaQiCount2;
  
  motorSum1 += BianMaQiCount1;
  motorSum2 += BianMaQiCount2;
  BianMaQiCount2=0;
}

void GetNewSpeedOldSpeed()
{                         
  u8 i=0;
  float fP=0,fI=0;
  float fDelta=0;
  float CarSpeed = 0;
  float tempc=0;
 // if(motorSum1 - motorSum2 > 5 || motorSum1 - motorSum2 < -5)
 //   CarSpeed=motorSum1>motorSum2?motorSum1+(motorSum1-motorSum2)/WanDaoJianSu*10.0:motorSum2+(motorSum2-motorSum1)/WanDaoJianSu*10.0;
//  else
    CarSpeed = (motorSum1 + motorSum2) / 2.0;
  //showWaveData[2] = (int)motorSum1+(motorSum1-motorSum2)/WanDaoJianSu;
//	showWaveData[3] = (int)1.35*(motorSum2+(motorSum2-motorSum1)/WanDaoJianSu);
  
	motorSum1 = motorSum2 = 0;
//	CarSpeed = CarSpeed * 0.05;//200.0/0.1;//单位转换，转/秒，编码盘200刻槽，0.1秒采集一次

  if(specialSpeedControl == 1)
  {
   /*	if(JiFenYCount == 9)     //检测坡道
   	{
   	 // showWaveData[0] = (int)JiFenY;
   	  UNIFORM_SPEED*=PoDaoJiaSuBiLi;
   	}
   	
   	if(speedUpTimer > speedUpTimerLimt)
    {
      speedDownTimer2 = 0;
      UNIFORM_SPEED/=PoDaoJiaSuBiLi;
    }
    
    if(speedUpTimer > 0)
     speedUpTimer++; */ 
   
   /* if(ZhangAiCount > 2 && speedDownTimer2 == 0)   //检测障碍
    {
      speedDownTimer2++;
      if(speedDownTimer2 == 1)  
        UNIFORM_SPEED/=ZhangAiBiLi;
    }

    if(speedDownTimer2 > 5)
    {
      speedDownTimer2 = 0;
      UNIFORM_SPEED*=ZhangAiBiLi;
    }
    
    if(speedDownTimer2 > 0)
     speedDownTimer2++;  */

    tempc = angleControlValue-lastAngleValue;
    if(tempc < 0)
      tempc = -tempc;
  	angleSum += tempc;
  		  
  	lastAngleValue = angleControlValue;
  	angleSumCount++;
  	if(angleSumCount >= 5)
  	{
  	  angleSum=0;
  	  angleSumCount=0;
  	}
   // showWaveData[1] = (int)angleSum;
    if(angleSum > HuangDangJianCe && speedDownTimer == 0) //检测晃荡
    {
      speedDownTimer = 1;
      UNIFORM_SPEED /= HuangDangJianCeBiLi ;
      //speedPart1 = (UNIFORM_SPEED-UNIFORM_SPEED/ZhangAiBiLi)/speedDownTimerLimt;
    }
    else
    {
      if(speedDownTimer > speedDownTimerLimt)
      {
        speedDownTimer = 0;
        UNIFORM_SPEED*=HuangDangJianCeBiLi;
      }
    }
    if(speedDownTimer > 0)
    {
      UNIFORM_SPEED -= speedPart1;
      speedDownTimer++;
    }
    
    //showWaveData[0] = (int)UNIFORM_SPEED;
  }
  
  if(StartSpeedUpTimer < 21 && StartSpeedUpTimer >= 1)//起始缓慢提速
  {
    StartSpeedUpTimer++;
    UNIFORM_SPEED += SpeedSetPart;
    //Pspeed += PspeedPart;
  } 
  
  if(PspeedTimer < 10 && PspeedTimer >= 1)
    PspeedTimer++;
  
  if(PspeedTimer == 10)
  {
    PspeedTimer = 31;
    P_SPEED /= 1.2;
  }
    
  fDelta = UNIFORM_SPEED - CarSpeed;

  fP = fDelta*P_SPEED;
  fI = fDelta/10.0*Dspeed;
  JiFenSpeed += fI;
  
  if(JiFenSpeed > 100.0)
    JiFenSpeed = 100.0;
  else if(JiFenSpeed < -100.0)
    JiFenSpeed = -100.0;
  //showWaveData[3] = (int)CarSpeed;
  speedOld = speedNew;
  speedNew = fP + JiFenSpeed;
}

void GetSpeedControlValue(u8 i)
{
  float fValue = speedNew - speedOld;
  speedControlValue = fValue * (i+1)/10.0 + speedOld;
}

void MotorPWMOut()
{
	fLeftVal = fRightVal = angleControlValue + speedControlValue;
//	showWaveData[0] = (int)fLeftVal;
	fLeftVal -= directionControlValue;
  fRightVal += directionControlValue;
	
//	showWaveData[0] = (int)angleControlValue;
//	showWaveData[1] = (int)directionControlValue;
//	showWaveData[2] = (int)speedControlValue;

	fLeftVal /=4.0;                 //匹配PWM值上限
	fRightVal /=4.0;
		
	if(fLeftVal > 0) 		          //电机死区偏差补偿	
	  fLeftVal += motorDeadVal*10;
	else if(fLeftVal< 0) 
	  fLeftVal -= motorDeadVal*10;
	if(fRightVal > 0)
	  fRightVal += motorDeadVal*10;
	else if(fRightVal < 0)
	  fRightVal -= motorDeadVal*10;
	
//	showWaveData[3] = (int)fRightVal;

//  fRightVal /= 1.3;
		
	if(fLeftVal > MOTOR_OUT_MAX)  //PWM值上限限制
	  fLeftVal = MOTOR_OUT_MAX;
	if(fLeftVal < MOTOR_OUT_MIN)
	  fLeftVal = MOTOR_OUT_MIN;
	if(fRightVal > MOTOR_OUT_MAX)
	  fRightVal = MOTOR_OUT_MAX;
	if(fRightVal < MOTOR_OUT_MIN)
	  fRightVal = MOTOR_OUT_MIN;	
	
//	showWaveData[3] = (int)fLeftVal;
//	showWaveData[3] = (int)fRightVal;
	
	if(fLeftVal <0)	                //电机转动
		Motor_No1_back(-(int)fLeftVal);	
	else                                  
		Motor_No1_forward((int)fLeftVal);     
	if(fRightVal <0)
		Motor_No2_back(-(int)fRightVal ); 
	else
		Motor_No2_forward((int)fRightVal );    
}

void delay()
{
  unsigned int i;
  for(i=0;i<10;i++)
  {
    asm("nop");
  }
}

//----------------------------------------------------------------------
//函 数 名:TSL1401_GetLine                                                       
//功    能:获得AD采样像素                                       
//参    数:*pixel  获得的像素值                          
//返    回:无                                                                                       
//----------------------------------------------------------------------
void TSL1401_GetLine(u16 *pixel)
{
  u8 i;
  //开始SI
  TSL1401_SI(0) ;
  TSL1401_CLK(0);
  delay();
  TSL1401_SI(1);
  delay();
  TSL1401_CLK(1);
  delay();
  TSL1401_SI(0);
  delay();
  //采集第1个点
  //AD配置成为8位精度，所以这里获得的是一个字节数据
  pixel[0] = ADCValue(3)/PixelOffset;
  TSL1401_CLK(0);
  
  //采集第2~128个点
  for(i=1; i<128; i++)
  {
    delay();
    TSL1401_CLK(1);
    delay(); 
    pixel[i] = ADCValue(3)/PixelOffset;
    TSL1401_CLK(0);
  }
  
  //发送第129个clk
   delay();
   TSL1401_CLK(1);
   delay(); 
   TSL1401_CLK(0);
   delay(); 
}

void OutputPixel() //用于CCD上位机软件调试
{
  u8 i=0;
  for(i=0; i<128; i++)
  {
    u8 tmp = gPixel[i];
    if(tmp==0xFF) 
      tmp = 0xFE; //遇到FF用FE替换即可
    UART0_SendByte(tmp);   
  }
  UART0_SendByte(0xFF);  //换行标记
}