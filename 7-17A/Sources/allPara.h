
//allPara.h
#include "NeededHeadFile.h"

#ifndef _ALLPARA_H_
#define _ALLPARA_H_

extern u8 Pangle,Dangle; 
extern int showWaveData[10];
extern s16 Zcenter,Gcenter;
extern float Rz,Rg;
extern float tg;
extern u8 carBalanceAngle;
extern u8 motorDeadVal;
extern u16 gPixel[128];
extern u8 PixelCenter;
extern s16 Rcenter;
extern u8 Pdirection,Ddirection;
extern u8 ThresholdOffset,PixelOffset;
extern u8 UniformSpeed;
extern u8 Pspeed,Dspeed;
extern u8 DirectionSpeedControlFlag;
extern int StartCount;
extern float UNIFORM_SPEED;
extern u8 WanDaoJianSu;
extern s16 Ycenter;
extern float SpeedSetPart;
extern u8 StartSpeedUpTimer;
extern float PspeedPart;
extern int SpeedUpTimeScale;
extern u8 specialSpeedControl;
extern float P_SPEED;
extern u8 PspeedTimer;
extern u8 specialPixelControl;
extern u8 startLineCheck;
#endif