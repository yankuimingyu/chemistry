#include "timer.h"
#include "led.h"
#include "GUI.h"
#include "usart.h"
#include "exti.h"
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ս��������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

extern __IO int32_t OS_TimeMS;
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//����TIM3ʱ�� 

	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;   //��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;	   //����ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;		   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//��������ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3,ENABLE);		  //ʹ��TIM3
}

void TIM3_IRQHandler(void)//����
{//int w;
	/*
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{	
		OS_TimeMS++;
	}
	*/
//	w=TIM3->CR1;
//	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			CLK_RATE=!CLK_RATE;
			LED0=!LED0;
				//Clk_freqence=!Clk_freqence;//Ƶ��
		}
}

//������ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��6!
void TIM6_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE); //��ʱ��6ʱ��ʹ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //���÷�Ƶֵ��10khz�ļ���Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;  //�Զ���װ��ֵ ������5000Ϊ500ms
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0; //ʱ�ӷָ�:TDS=Tck_Tim
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update|TIM_IT_Trigger,ENABLE); //ʹ��TIM6�ĸ����ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn; //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ʹ��ͨ��
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM6,ENABLE); //��ʱ��6ʹ��
}

//������
void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
	{
		GUI_TOUCH_Exec();
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update); //����жϱ�־λ
}

void TIM4_PWM_Init(u16 arr,u16 psc)//����PB6��
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	 GPIO_InitTypeDef  GPIO_InitStructure;
	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 

  /* GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
////	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��4ʱ��
// 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4, DISABLE); 
//	

//		//
//	 /*====== ��ʼ��TIM4 ======*/
//	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ


//	/*====== ��ʼ��TIM4 Channel1 PWMģʽ Heater 12~17======*/ 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_Pulse=0;//����
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //TIM_OCPolarity_Low �������:TIM����Ƚϼ��Ե�
//	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC1
//	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
//	//TIM_ARRPreloadConfig(TIM4,ENABLE);
//	 
	 /*=================================*/
	   /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = arr;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = psc;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ36MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	    //����ΪPWMģʽ2
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 0;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ

  TIM_OC1Init(TIM4, &TIM_OCInitStructure);	 //ʹ��ͨ��1

  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	  //GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM4 clock enable */
	//PCLK1����2��Ƶ����ΪTIM4��ʱ��Դ����36MHz


  /*GPIOB Configuration: TIM4 channel 1 and 2 and 3 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	

	
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
	

}



void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//����TIM3ʱ�� 

	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;   //��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;	   //����ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;		   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//��������ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM4,ENABLE);		  //ʹ��TIM3
}

//
void TIM5_Int_Init(u16 arr,u16 psc)
	{
			TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE); //��ʱ��5ʱ��ʹ��
			
			TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //���÷�Ƶֵ��10khz�ļ���Ƶ��
			TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
			TIM_TimeBaseInitStructure.TIM_Period=arr;  //�Զ���װ��ֵ ������5000Ϊ500ms
			TIM_TimeBaseInitStructure.TIM_ClockDivision=0; //ʱ�ӷָ�:TDS=Tck_Tim
			TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
			
			TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_Trigger,ENABLE); //ʹ��TIM5�ĸ����ж�

			NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //TIM5�ж�
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1��
			NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;  //�����ȼ�3��
			NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ʹ��ͨ��
			NVIC_Init(&NVIC_InitStructure);
			
			TIM_Cmd(TIM5,ENABLE); //��ʱ��5ʹ��
	}

//



void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ�ܶ�ʱ��2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
  
	
	AFIO->MAPR&=0XF8FFFFFF;  //�ر�JTD1��JTD0
  AFIO->MAPR|=0X04000000;  //��ΪJTAGռ����PB3��PA15�����︴����PB3���ţ��������Σ�ʹ��PB3�����PWM��
	
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);//�����ˣ�ʲôʱ����ʲôʱ�� ������
	//���ø����Ź���,���TIM2 CH2��PWM���岨��	GPIOB.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
	 //GPIO_ResetBits(GPIOB,GPIO_Pin_3);	
 
   //��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM2 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM2 OC2

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR3�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
	

}

void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    
 
   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
	

}
//TIM2_Encoder_Init,Tim2_CH1(PA0);Tim2_CH2(PA1)
//arr���Զ���װֵ 0XFFFF
//psc��ʱ��Ԥ��Ƶ��        ������Ƶ
//��STM32�����ֲ� 14.3.12�������ӿ�ģʽ

// ��Ҫȷ������
void TIM2_Encoder_Init(u16 arr,u16 psc)
{
    RCC->APB1ENR|=1<<0;       //TIM2ʱ��ʹ��
        RCC->APB2ENR|=1<<2;       //ʹ��PORTAʱ��
        
    GPIOA->CRL&=0XFFFFFF00;   //PA0��PA1 ���֮ǰ����
    GPIOA->CRL|=0X00000044;   //PA0��PA1 ��������
            
    TIM2->ARR=arr;            //�趨�������Զ���װֵ 
    TIM2->PSC=psc;            //Ԥ��Ƶ��

        TIM2->CCMR1 |= 1<<0;          //����ģʽ��IC1FP1ӳ�䵽TI1��
        TIM2->CCMR1 |= 1<<8;          //����ģʽ��IC2FP2ӳ�䵽TI2��
        TIM2->CCER |= 0<<1;                  //IC1������
        TIM2->CCER |= 0<<5;           //IC2������
    TIM2->SMCR |= 3<<0;                  //����������������ػ��½�����Ч
        TIM2->CR1 |= 1<<0;                  //ʹ�ܼ�����
}
//�����Ĵ�����ֵ
void TIM2_Encoder_Write(int data)
{
    TIM2->CNT = data;
}
//����������
int TIM2_Encoder_Read(void)
{
    TIM2_Encoder_Write(0);        //��������0
        //delay_ms(10);          //���ʱ�䣬�ɵ���
    return (int)((s16)(TIM2->CNT));           //��������ת��
                             //��¼���ر仯������һ��դ�񱻼�¼4�Σ�
}
//�����������ת��Ȧ��
void Encode_read()//����жϴ�����Ӳ���жϴ���
{
		TIM2_Encoder_Init(6355,0);//����Ƶ
		
	
	
}


//�ⲿ�ж�0����̽����� ���Ŷ�Ӧ���ж�
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    //KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

//   //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
//  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

//   //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY0
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
//  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


//   //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
// 	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}

////�ⲿ�ж�0������� 
//void EXTI0_IRQHandler(void)
//{
//	delay_ms(10);//����
//	if(WK_UP==1)	 	 //WK_UP����
//	{				 
//		BEEP=!BEEP;	
//	}
//	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
//}
 
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
//	if(KEY2==0)	  //����KEY2
//	{
//		LED0=!LED0;
//		//BEEP=!BEEP;
//	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
}
