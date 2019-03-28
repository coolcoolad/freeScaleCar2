
//SCI.h

#ifndef _SCI_
#define _SCI_

void SCI_Init(void);
void UART0_SendByte(byte ch);
void UART0_SendPacket(byte *pBuf,int pBuf_Length);
void ShowWave(void);

#endif