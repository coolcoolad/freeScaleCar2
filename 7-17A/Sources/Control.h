
//Control.h

#ifndef _CONTROL_
#define _CONTROL_

void AllParaInit();
void GetGcenterRcenter();

void GetZangleGangle();
void GetAngleControlValue();

void TSL1401_GetLine(u16 *pixel);
int CheckStartLine(u16 *pixel);
void OutputPixel();
void GetYsubYaddDIRangle(u16 *pixel);
void GetDirectionControlValue(u8 i);

void GetMotorPlus();
void GetNewSpeedOldSpeed();
void GetSpeedControlValue(u8 i);

#endif