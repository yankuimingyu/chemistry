#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	

								    
 //////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//DAC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/8
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
								    

void Dac1_Init(void);//回环模式初始化	
//vol:0~3300,代表0~3.3V
void Dac1_Set_Vol(u16 vol);
//DAC_SetChannel1Data(DAC_Align_12b_R, 0);//初始值为0	  
#endif

















