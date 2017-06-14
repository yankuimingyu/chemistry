#include "led.h"

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


#define BEEP PBout(8)	// BEEP,蜂鸣器接口		 

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5);

}


///
void LED_Init_2(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	//要重定义？by yan
	AFIO->MAPR&=0XF8FFFFFF;  //关闭JTD1与JTD0
  AFIO->MAPR|=0X04000000;  //
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
//	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED0-->PB.7 端口配置  ENABLE
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //推挽输出复用
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.7
 //GPIO_SetBits(GPIOB,GPIO_Pin_7);						 //PB.7 输出高
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	
/*	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.6
 GPIO_ResetBits(GPIOB,GPIO_Pin_6);						 //PB.6 输出低
 */
	
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	//LED0-->PB.5 端口配置   DIR
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOE,GPIO_Pin_4);						 //PB.5 输出高
 GPIO_ResetBits(GPIOE,GPIO_Pin_4);	
	
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	//LED0-->PB.5 端口配置   DIR
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOE,GPIO_Pin_2);						 //PB.5 输出高
 GPIO_ResetBits(GPIOE,GPIO_Pin_2);
					 //PB.5 输出高
	/*
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //   CLK
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.9
 GPIO_ResetBits(GPIOB,GPIO_Pin_9);						 //旧版作为步进电机 step信号
*/
/// 步进电机控制 PB4 step;PB3 en； PB9 dir;new virsion
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //   CLK step
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.4
 GPIO_ResetBits(GPIOB,GPIO_Pin_4);	
 //新版作为步进电机 step信号
 
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //   CLK
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.4
 GPIO_SetBits(GPIOB,GPIO_Pin_3);						 //新版做使能控制

		

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //   CLK 新版做方向控制步进电机
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.9
 GPIO_ResetBits(GPIOB,GPIO_Pin_9);						 //旧版作为步进电机 step信号
 
 ///
 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	 //根据参数初始化GPIOB.8
 GPIO_ResetBits(GPIOB,GPIO_Pin_8);	
 
 
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
//	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //复用推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //使能PB,G端口时钟
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG  | RCC_APB2Periph_AFIO, ENABLE);  //使

 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				 //   CLK
 GPIO_Init(GPIOG, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.4
 GPIO_SetBits(GPIOG,GPIO_Pin_14);	
}


///
void LED_ON_OFF(int led1,int on_off,int turn_right_left)
{
	if(on_off==1)
	{
		 //GPIO_SetBits(GPIOE,GPIO_Pin_5);
		if(turn_right_left==1)
		{
			GPIO_ResetBits(GPIOE,led1);
			GPIO_SetBits(GPIOB,led1);
			
			
		}
		else if(turn_right_left==0)
		{
			GPIO_ResetBits(GPIOB,led1);
			GPIO_SetBits(GPIOE,led1);
			
			
		}
	}
	else if(on_off==0)
	{ if(turn_right_left==0)
		{
			GPIO_SetBits(GPIOE,led1);
			GPIO_SetBits(GPIOB,led1);
		}
		else if(turn_right_left==0)
		{
			GPIO_SetBits(GPIOB,led1);
			GPIO_SetBits(GPIOE,led1);
		}
		
		
	}
	
}

void GpioB_GpioE_init(int GpioE_pin,int GpioB_pin)
{
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GpioB_pin;				 //Enable
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_ResetBits(GPIOB,GpioB_pin);						 //PB.5 输出低

 GPIO_InitStructure.GPIO_Pin = GpioE_pin;	    		 //step
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOE,GpioE_pin); 						 //PE.5 输出低 
	
}
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //step
// GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_ResetBits(GPIOE,GPIO_Pin_6); 						 //PE.5 输出低
	


void GpioB_GpioE_stir(int GpioE_dir,int GpioB_clk,int Gpio_En)
{
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GpioE_dir;				 //Enable
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_ResetBits(GPIOB,GpioE_dir);						 //PB.5 输出低

 GPIO_InitStructure.GPIO_Pin = GpioB_clk;	    		 //step
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOE,GpioB_clk); 						 //PE.5 输出低 
	
	 GPIO_InitStructure.GPIO_Pin = Gpio_En;	    		 //step
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOE,Gpio_En); 						 //PE.5 输出低 
	
}
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //step
// GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_ResetBits(GPIOE,GPIO_Pin_6); 						 //PE.5 输出低
	
//速度设定	
void Washing(int stop)
{
 switch(stop)
 
 {
   case 1:
	 GPIO_SetBits(GPIOB,GPIO_Pin_6);
	 GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	 break;
	 case 0:
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
	 GPIO_SetBits(GPIOE,GPIO_Pin_3);
	 
	 break;
 }

}	
