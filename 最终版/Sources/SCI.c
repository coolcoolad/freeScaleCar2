
//SCI.c
#include "NeededHeadFile.h"
#include "allPara.h"

//-----------------------------------------------------
void SCI_Init(void) 
{     
    SCI0CR1 =0x00;
    SCI0CR2 =0x2c; //enable Receive Full Interrupt,RX enable,Tx enable      
    SCI0BD  =35;   //115200
                  //SCI0BDL=busclk/(16*SCI0BDL)
                  //busclk  8MHz, 9600bps,SCI0BD=0x34
                  //busclk 16MHz, 9600bps,SCI0BD=0x68
                  //busclk 24MHz, 9600bps,SCI0BD=0x9C
}                 //busclk 32MHz, 9600bps,SCI0BD=0xD0  
                  //busclk 40MHz, 9600bps,SCI0BD=0x106

void UART0_SendByte(byte ch)
{
  while(!(SCI0SR1&0x80));
  SCI0DRL = ch; 
}

//---------------------------------------------------------------------
// 函数功能：SCI0发送字符串数据
// 形式参数：   byte *pBuff     发送缓冲区
//              int Length 发送字节的长度 
// 函数返回值：无   
//---------------------------------------------------------------------
void UART0_SendPacket(byte *pBuf,int pBuf_Length) 
{
  int i;
  for(i=0;i<pBuf_Length;i++)
  {
    while(!(SCI0SR1&0x80));
    SCI0DRL=*(pBuf+i); 
  }
}

void ShowWave(void) 
{
  uchar OutData[20];
  uchar i = 0;
	uchar tmp = 0;
	
	OutData[0] = 0x88;
	OutData[1] = 0xA1;
	OutData[2] = 0x08;
	OutData[3] = (showWaveData[0]&0xFF00)>>8;
	OutData[4] = showWaveData[0];
	OutData[5] = (showWaveData[1]&0xFF00)>>8;
	OutData[6] = showWaveData[1];
	OutData[7] = (showWaveData[2]&0xFF00)>>8;
	OutData[8] = showWaveData[2];
	OutData[9] = (showWaveData[3]&0xFF00)>>8;
	OutData[10] = showWaveData[3];

	for(i = 0; i < 11;i++)
	{
		tmp += OutData[i];
	}
	OutData[11] = tmp;
	
	UART0_SendPacket(OutData,12);
} 