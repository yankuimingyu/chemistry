#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
u16 Get_Adc_Middle_value(u8 ch,u8 times);//��λֵ�����Ͼ���Զ
u16	Get_Adc_Middle_Average(u8 ch,u8 times);//��λƽ��ֵ�����Ͼ���Զ
char *Float_to_string(float data);
float ADCvalue_test(void);
float Concentration_return(float k,float Vc0,float Vc);
 
#endif 
