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
#include "NANJING.h"
#include  "FramewinDLG.h"
//#include "WindowDLG.h"
//#include "GUIDemo.h"

//#include "DIALOG.h"

int main(void)
{	



// 
//			delay_init();	    	//延时函数初始化	  
//			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//			//uart_init(115200);	 	//串口初始化为115200
//			//LED_Init();			    //LED端口初始化
//			TFTLCD_Init();			//LCD初始化	
//			//KEY_Init();	 			//按键初始化
//			TP_Init();				//触摸屏初始化
//			FSMC_SRAM_Init();		//初始化SRAM
//			TIM3_Int_Init(999,71);	//1KHZ 定时器1ms 
//			TIM6_Int_Init(999,719);	//10ms中断
//			
			 
			delay_init();	    	//延时函数初始化	  
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
			uart_init(115200);	 	//串口初始化为115200///跟显示是什么关系。
			LED_Init();			    //LED端口初始化
			TFTLCD_Init();			//LCD初始化	
			//KEY_Init();	 			//按键初始化
			TP_Init();				//触摸屏初始化
			FSMC_SRAM_Init();		//初始化SRAM
			//TIM3_Int_Init(999,71);	//1KHZ 定时器1ms 
			TIM6_Int_Init(999,719);	//10ms中断
			
			
			my_mem_init(SRAMIN); 		//初始化内部内存池
			my_mem_init(SRAMEX);  		//初始化外部内存池
			
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//使能CRC时钟，否则STemWin不能使用 
			
			
	
				WM_SetCreateFlags(WM_CF_MEMDEV); 	//启动所有窗口的存储设备 必要
				GUI_Init();  						//STemWin初始化
	
	
			//CreateWindow(); 
				
	
////	
////			GUI_Clear();
//			GUI_Init();
//			GUI_SetBkColor(GUI_WHITE);
//			GUI_SetColor(GUI_BLACK);
//			//GUI_SetFont(&GUI_Font16_ASCII);
//			GUI_DispStringAt("Hello world!",80,200);
////			//	CreateWindow();
			
			//WM_SetCreateFlags(WM_CF_MEMDEV); 	//启动所有窗口的存储设备
			//GUI_Init();  						//STemWin初始化
			
			
			
			//CreateWindow();
			//CreateFramewin();
		
			CreateNANJING();
			
		
		//	while(1)
				//{
				//MainTask();
			//		delay_ms(100);
					//GUI_Delay(100); //延时固定必须要
			//	}
			//while(1);
//			//
//	
//			GUI_SetBkColor(GUI_BLUE); // 设置背景颜色
//      GUI_SetColor(GUI_YELLOW);
//			GUI_SetFont(&Font24_ASCII);
//			GUI_DispStringAt("Hello Word!",0,0); //
//	
//	
//			
//			//
//			while(1);
}


