#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	

								    
 //////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DAC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
								    

void Dac1_Init(void);//�ػ�ģʽ��ʼ��	
//vol:0~3300,����0~3.3V
void Dac1_Set_Vol(u16 vol);
//DAC_SetChannel1Data(DAC_Align_12b_R, 0);//��ʼֵΪ0	  
#endif
















