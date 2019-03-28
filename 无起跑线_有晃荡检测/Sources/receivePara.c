
//receivePara.c
#include "stdtypes.h"
#include <MC9S12XS128.h>     /* derivative information */
#include "receivePara.h"
#include "allPara.h"
#include "printp.h"

uchar paraTmp[READ_NUMBER];         

void receivePara() 
{
  uchar ch;
	uchar i = 0;
	uchar paraTmp[READ_NUMBER];	
	while(1) {
	  if(PORTA_PA6  == 1 || i >= READ_NUMBER) 
    {
      break;
    }
	  ch = uart_r();
	  paraTmp[i]=ch;
	  i++;
	}
	Pangle = paraTmp[0];
	Dangle = paraTmp[1];
	carBalanceAngle = paraTmp[2];
	
  Pdirection = paraTmp[3];
  Ddirection = paraTmp[4];
  PixelCenter = paraTmp[5];
  ThresholdOffset = paraTmp[6];
  PixelOffset = paraTmp[11];
  
  Pspeed = paraTmp[9];
  Dspeed = paraTmp[10];
  UniformSpeed = paraTmp[8];
  WanDaoJianSu = paraTmp[12];
  	
	motorDeadVal = paraTmp[7];
	

	if(i == READ_NUMBER) uart_t('o');
  	else uart_t('e');
	while(PORTA_PA6  == 0);//拨码开关拨为1后参数起效
}