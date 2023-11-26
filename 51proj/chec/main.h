#ifndef __MAIN_H__
#define __MAIN_H__

#define u8 unsigned char
#define u16 unsigned int



void SysInit(void);
void delay(u16 time);
void scan();
void Set_moto(u8 dutya, u8 dutyb, u8 runmode);
#endif /** __MAIN_H__ */

