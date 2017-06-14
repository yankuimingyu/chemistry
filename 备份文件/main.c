#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ILI93xx.h"
#include "usart.h"	 
#include "24cxx.h"
#include "flash.h"
#include "touch.h"
#include "sram.h"
#include "timer.h"
#include "malloc.h"
#include "GUI.h"
#include "WindowDLG.h"
//#include "GUIDemo.h"

//#include "DIALOG.h"
/************************************************
 ALIENTEKս��STM32������STemWinʵ��
 STemWin ��ֲʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

//extern 	 CreateWindow(void);

int main(void)
{	



 
			delay_init();	    	//��ʱ������ʼ��	  
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
			uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
			LED_Init();			    //LED�˿ڳ�ʼ��
			TFTLCD_Init();			//LCD��ʼ��	
			KEY_Init();	 			//������ʼ��
			TP_Init();				//��������ʼ��
			FSMC_SRAM_Init();		//��ʼ��SRAM
			TIM3_Int_Init(999,71);	//1KHZ ��ʱ��1ms 
			TIM6_Int_Init(999,719);	//10ms�ж�
			
			
			
			my_mem_init(SRAMIN); 		//��ʼ���ڲ��ڴ��
			my_mem_init(SRAMEX);  		//��ʼ���ⲿ�ڴ��
			
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//ʹ��CRCʱ�ӣ�����STemWin����ʹ�� 
			
			
	
				WM_SetCreateFlags(WM_CF_MEMDEV); 	//�������д��ڵĴ洢�豸 ��Ҫ
				GUI_Init();  						//STemWin��ʼ��
	
	
			//CreateWindow(); 
				
	
////	
////			GUI_Clear();
//			GUI_Init();
//			GUI_SetBkColor(GUI_WHITE);
//			GUI_SetColor(GUI_BLACK);
//			//GUI_SetFont(&GUI_Font16_ASCII);
//			GUI_DispStringAt("Hello world!",80,200);
////			//	CreateWindow();
			
			//WM_SetCreateFlags(WM_CF_MEMDEV); 	//�������д��ڵĴ洢�豸
			//GUI_Init();  						//STemWin��ʼ��
			
			
			
			CreateWindow();
		//	CreateFramewin();
			while(1)
				{
					GUI_Delay(1000); //��ʱ�̶�����Ҫ
				}
			//while(1);
//			//
//	
//			GUI_SetBkColor(GUI_BLUE); // ���ñ�����ɫ
//      GUI_SetColor(GUI_YELLOW);
//			GUI_SetFont(&Font24_ASCII);
//			GUI_DispStringAt("Hello Word!",0,0); //
//	
//	
//			
//			//
//			while(1);
}


