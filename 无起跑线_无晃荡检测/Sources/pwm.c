
//PWM.c

#include "NeededHeadFile.h" 
#include "pwm.h"    //PWM头文件
#include "allPara.h"

void PWMInit(void) 
{ 
    PWMCTL_CON45 =1;	//级联
  	PWMCTL_CON67 =1;
  	PWMCTL_CON23 =1;
  	PWMCTL_CON01 =1;
  	
    PWMCAE=0X00;      //0左对齐 1中心对齐
    PWMPRCLK=0X00;    //1分频
    
    PWMCLK_PCLK5 =1;	//Clock SA
  	PWMCLK_PCLK3 =1;	//Clock SB
  	PWMCLK_PCLK7 =1;	//clock SB
  	PWMCLK_PCLK1 =1;	//clock SA      
  	
  	PWMSCLA=1;       //ClockSA=ClockA/(2*PWMSCLA)=64000k/(2*1)=32MHZ
    PWMSCLB=1;        //ClockSB=ClockA/(2*PWMSCLB)=64000k/(2*1)=32MHZ
    
    PWMPOL_PPOL5 =1;             //极性全设置为正
  	PWMPOL_PPOL7 =1;             //极性全设置为正
  	PWMPOL_PPOL1 =1;             //极性全设置为正
  	PWMPOL_PPOL3 =1;      //输出极性选择 0起始为低电平 1起始为高电平
    
  	PWMPER45 =2000;
  	PWMPER01 =2000;
  	PWMPER23 =2000;              //16KHZ
  	PWMPER67 =2000;              //16KHZ  

    PWME=0x00;        
    return;
}
//----------------------------------------------*
//功  能:直流电机正转                                  *
//参  数:unsigned int duty,占空比值                                              *
//返  回:无                                      *
//-------------------------------------------------------------------------*
void Motor_No1_forward(unsigned int duty)
{
  PORTB_PB0 = 1;
  PWME_PWME3 = 1;
  PWME_PWME1 = 0;
  DDRP_DDRP1 = 1;
  PTP_PTP1 = 0;

  PWMDTY23 = duty;
}
void Motor_No2_forward(unsigned int duty)
{
  PORTB_PB1 = 1;
  PWME_PWME7 = 1;
  PWME_PWME5 = 0;
  DDRP_DDRP5 = 1;
  PTP_PTP5 = 0;

  PWMDTY67 = duty;
}
//----------------------------------------------*
//功  能:直流电机反转                                  *
//参  数:unsigned int duty,占空比值                                              *
//返  回:无                                      *
//-------------------------------------------------------------------------*
void Motor_No1_back(unsigned int duty)
{  
  PORTB_PB0 = 1;
  PWME_PWME1 = 1;
  PWME_PWME3 = 0;
  DDRP_DDRP3 = 1;
  PTP_PTP3 = 0;

  duty = duty;
  PWMDTY01 = duty;
}
void Motor_No2_back(unsigned int duty)
{  
  PORTB_PB1 = 1;
  PWME_PWME5 = 1;
  PWME_PWME7 = 0;
  DDRP_DDRP7 = 1;
  PTP_PTP7 = 0;

  PWMDTY45 = duty;
}

