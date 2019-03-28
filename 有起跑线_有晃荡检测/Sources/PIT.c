/******************************************
**
 *	File include:PIT timer module
 *
 *
 *	note:
 *	PIT0、PIT1、PIT2、PIT3 对应的中断向量号分别为 66、67、68、69
 *	 time-out period = (PITMTLD + 1) * (PITLD + 1) / fBUS.
 *
 ******************************************/
 
 
 #include "PIT.h"
 #include "hidef.h"

/*-----------------PIT0初始化--------10ms----------*/ 
void PIT_Init(void)
{
  DisableInterrupts;
	PITCFLMT=0x00;          //disable PIT
  //PITTF = 0x01;
  
	PITCE_PCE0=1;             //enable timer channel 0
	PITMUX_PMUX0=0;           //ch0 connected to micro timer 0
	PITMTLD0=15 ;           //micro time base 0 equals 255 clock cycles   
	PITLD0=39999;            //time-out period = (PITMTLDx + 1) * (PITLDx + 1) / fBUS.
  PITINTE_PINTE0=1; //0通道定时器定时中断被使能

	PITCFLMT=0x80;          //enable PIT
	EnableInterrupts;
}


