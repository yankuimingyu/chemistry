#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define Clk_freqence PBout(8)//Ƶ��
#define LED1 PEout(5)// PE5	
//#define CLK_RATE PBout(9)// PB9 �ɰ�
#define CLK_RATE PBout(4)// PB4 �°��//
//�µĵ�·������� I/O���� pb4 2016-2-6

void LED_Init(void);//��ʼ��
void LED_Init_2(void);//
void LED_ON_OFF(int led1,int on_off,int turn_right_left);
void Washing_cotrol(int stop);
void  Washing(int stop);
void GpioB_GpioE_init(int GpioE_pin,int GpioB_pin);
void GpioB_GpioE_stir(int GpioE_dir,int GpioB_clk,int Gpio_En);

		 				    
#endif
