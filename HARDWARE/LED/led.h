#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define Clk_freqence PBout(8)//频率
#define LED1 PEout(5)// PE5	
//#define CLK_RATE PBout(9)// PB9 旧版
#define CLK_RATE PBout(4)// PB4 新版版//
//新的电路板搅拌电机 I/O口是 pb4 2016-2-6

void LED_Init(void);//初始化
void LED_Init_2(void);//
void LED_ON_OFF(int led1,int on_off,int turn_right_left);
void Washing_cotrol(int stop);
void  Washing(int stop);
void GpioB_GpioE_init(int GpioE_pin,int GpioB_pin);
void GpioB_GpioE_stir(int GpioE_dir,int GpioB_clk,int Gpio_En);

		 				    
#endif
