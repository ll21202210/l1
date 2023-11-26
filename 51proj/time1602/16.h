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


#define cls 0x01 //����
/**  ģʽ����ָ�� */
#define i0s0 0x04 //������� ��ʾ�����ƶ� 
#define i1s0 0x06 //������� ��ʾ�����ƶ�
#define i0s1 0x05 //������� ��ʾ����������1���ַ�
#define i1s1 0x07 //������� ��ʾ����������1���ַ�
/** ��ʾ���ؿ���  ���ʹ�� */
#define dison 0x0c //��ʾ����
#define ygb 0x0a //�й��
#define gbs 0x09 //�����˸
/** �����趨 */
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
/** ��ַ˵��:
��һ�� 0x00 0x01 ~ 0x0f
�ڶ��� 0x40 0x41 ~~ 0x4f
LCM16wadd �������Զ����ڰ�λ��1
*/
/**
CGRAM���Դ洢8���Զ����ַ���
�����ڴ洢���е��׵�ַ�ֱ�Ϊ:
0x40,0x48,0x50,0x58,0x60,0x68,0x70,0x78
*/


void LCM16wcmd(u8 cmd);
void LCM16wdat(u8 dat);
void LCM1602Init(void);
void Delay200us();
void Delay2ms();
#endif /** _16_H_ */
