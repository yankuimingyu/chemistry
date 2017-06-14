#include "led.h"

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


#define BEEP PBout(8)	// BEEP,�������ӿ�		 

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5);

}


///
void LED_Init_2(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	//Ҫ�ض��壿by yan
	AFIO->MAPR&=0XF8FFFFFF;  //�ر�JTD1��JTD0
  AFIO->MAPR|=0X04000000;  //
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
//	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED0-->PB.7 �˿�����  ENABLE
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.7
 //GPIO_SetBits(GPIOB,GPIO_Pin_7);						 //PB.7 �����
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	
/*	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.6
 GPIO_ResetBits(GPIOB,GPIO_Pin_6);						 //PB.6 �����
 */
	
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	//LED0-->PB.5 �˿�����   DIR
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOE,GPIO_Pin_4);						 //PB.5 �����
 GPIO_ResetBits(GPIOE,GPIO_Pin_4);	
	
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	//LED0-->PB.5 �˿�����   DIR
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOE,GPIO_Pin_2);						 //PB.5 �����
 GPIO_ResetBits(GPIOE,GPIO_Pin_2);
					 //PB.5 �����
	/*
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //   CLK
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.9
 GPIO_ResetBits(GPIOB,GPIO_Pin_9);						 //�ɰ���Ϊ������� step�ź�
*/
/// ����������� PB4 step;PB3 en�� PB9 dir;new virsion
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //   CLK step
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.4
 GPIO_ResetBits(GPIOB,GPIO_Pin_4);	
 //�°���Ϊ������� step�ź�
 
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //   CLK
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.4
 GPIO_SetBits(GPIOB,GPIO_Pin_3);						 //�°���ʹ�ܿ���

		

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //   CLK �°���������Ʋ������
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.9
 GPIO_ResetBits(GPIOB,GPIO_Pin_9);						 //�ɰ���Ϊ������� step�ź�
 
 ///
 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8
 GPIO_ResetBits(GPIOB,GPIO_Pin_8);	
 
 
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
//	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�����������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��PB,G�˿�ʱ��
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ

 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				 //   CLK
 GPIO_Init(GPIOG, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.4
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
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GpioB_pin;				 //Enable
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_ResetBits(GPIOB,GpioB_pin);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GpioE_pin;	    		 //step
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOE,GpioE_pin); 						 //PE.5 ����� 
	
}
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //step
// GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
// GPIO_ResetBits(GPIOE,GPIO_Pin_6); 						 //PE.5 �����
	


void GpioB_GpioE_stir(int GpioE_dir,int GpioB_clk,int Gpio_En)
{
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GpioE_dir;				 //Enable
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_ResetBits(GPIOB,GpioE_dir);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GpioB_clk;	    		 //step
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOE,GpioB_clk); 						 //PE.5 ����� 
	
	 GPIO_InitStructure.GPIO_Pin = Gpio_En;	    		 //step
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOE,Gpio_En); 						 //PE.5 ����� 
	
}
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //step
// GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
// GPIO_ResetBits(GPIOE,GPIO_Pin_6); 						 //PE.5 �����
	
//�ٶ��趨	
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
