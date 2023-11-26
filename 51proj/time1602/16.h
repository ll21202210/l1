#ifndef _16_H_
#define _16_H_

#include <reg52.h>
#include <intrins.h>

#define u8 unsigned char
#define u16 unsigned int

#define LCM16Dat P0

sbit LCM16RD =  P2^6;
sbit LCM16WR = P2^5;
sbit LCM16EN = P2^7;


#define cls 0x01 //清屏
/**  模式设置指令 */
#define i0s0 0x04 //光标左移 显示屏不移动 
#define i1s0 0x06 //光标右移 显示屏不移动
#define i0s1 0x05 //光标左移 显示屏整体右移1个字符
#define i1s1 0x07 //光标右移 显示屏整体右移1个字符
/** 显示开关控制  组合使用 */
#define dison 0x0c //显示开启
#define ygb 0x0a //有光标
#define gbs 0x09 //光标闪烁
/** 功能设定 */
#define modes1 0x38
/** CGRAM */
#define cgram1 0x40
#define cgram2 0x48
#define cgram3 0x50
#define cgram4 0x58
#define cgram5 0x60
#define cgram6 0x68
#define cgram7 0x70
#define cgram8 0x78
/** 地址说明:
第一行 0x00 0x01 ~ 0x0f
第二行 0x40 0x41 ~~ 0x4f
LCM16wadd 函数会自动将第八位置1
*/
/**
CGRAM可以存储8个自定义字符，
他们在存储器中的首地址分别为:
0x40,0x48,0x50,0x58,0x60,0x68,0x70,0x78
*/


void LCM16wcmd(u8 cmd);
void LCM16wdat(u8 dat);
void LCM1602Init(void);
void Delay200us();
void Delay2ms();
#endif /** _16_H_ */
