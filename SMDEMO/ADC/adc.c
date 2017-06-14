 #include "adc.h"
 #include "delay.h"
 #include "stm32f10x_adc.h"
 #include "math.h"
//////////////////////////////////////////////////////////////////////////////////	 
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
	   
		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_1Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(4);
	}
	return temp_val/times;
} 	 
//��λֵ���˲� �Ͼ�����ѧԺ �Ͽ�
u16	Get_Adc_Middle_value(u8 ch,u8 times)//times����ҪС��15
	{
		u32 value_buf[15],temp=0;
		u8 count,i,j;
		count=times;
		for ( count=0;count<times;count++)
			{
			value_buf[count] = Get_Adc(ch);
			delay_ms(4);
			}
		for (j=0;j<times-1;j++)
		{
			for (i=0;i<times-j;i++)
			{
				if ( value_buf[i]>value_buf[i+1] )
				{
				temp = value_buf[i];
				value_buf[i] = value_buf[i+1]; 
				value_buf[i+1] = temp;
				}
			}
		}
		//for(count=1;count<times-1;count++)//ȥ��һ�����ȥ��һ����� ����ƽ��
			//sum += value_buf[count];
		//return (char)(sum/(N-2));
		return value_buf[(times-1)/2];
	}

//
u16	Get_Adc_Middle_Average(u8 ch,u8 times)//times����ҪС��15
	{
		u32 value_buf[15],temp,sum;
		u8 count,i,j;
		count=times;
		for ( count=0;count<times;count++)
			{
			value_buf[count] = Get_Adc(ch);
				;//��ʱ
			//delay_ms(4);
			}
		for (j=0;j<times-1;j++)
		{
			for (i=0;i<times-j;i++)
			{
				if ( value_buf[i]>value_buf[i+1] )
				{
				temp = value_buf[i];
				value_buf[i] = value_buf[i+1]; 
				value_buf[i+1] = temp;
				}
			}
		}
		
		for(count=1;count<times-1;count++)//ȥ��һ�����ȥ��һ����� ����ƽ��
		{
			sum += value_buf[count];
		}
		return (sum/(times-2));
		//return value_buf[(times-1)/2];
	}


//float to strings
	

		// ������ת�����ַ���
// ������data
// ���أ�str
char  *Float_to_string(float data)
{	static char str[20];
		long i,j,k,temp,x;
		char intpart[20], dotpart[20];  // �����������ֺ�С������

		//1.ȷ������λ
		if(data<0) {str[0]='-';data=-data;}
		else str[0]=' ';

		//2.ȷ����������
		temp=(long)data;//ȥ����С������
		//data=data-temp;//data ֻʣ��С������

		i=0;
		x=temp/10;
		while(x!=0)//??wΪʲôҪ������ô��
			{
				intpart[i]=temp-10*x+48; //to ascii code
				temp=x;
				x=temp/10;
				i++;
			}
		intpart[i]=temp+48;

		//3.ȷ��С������,ȡ��12λС��
		data=data-(long)data;
		for(j=0;j<4;j++)//��ʾ��λ��
			{
				dotpart[j]=(int)(data*10)+48;
				data=data*10.0;
				data=data-(long)data;
			}

		//4.������װ
		for(k=1;k<=i+1;k++) str[k]=intpart[i+1-k];
		str[i+2]='.';
		for(k=i+3;k<i+j+3;k++) str[k]=dotpart[k-i-3];
		str[i+j+3]=0x0D;
		//str[]="";
		
		return str;

}





float ADCvalue_test() //��ʾADCֵ����
		{//
				u16 adcx;//,datastoreOri_3[400];
				float x_test;
			  //for(i=0;i<3;i++){
				adcx=Get_Adc_Middle_value(ADC_Channel_1,15);//�������ƽ������
				x_test=(float)adcx*(3.3/4096);
				//}
			
			return  x_test;//����ֵ
		}




float ADCvalue_test_parameter() //��ʾADCֵ����
		{//
				u16 adcx;//,datastoreOri_3[400];
				float x_test;
			  //for(i=0;i<3;i++){
				adcx=Get_Adc_Middle_value(ADC_Channel_1,15);//�������ƽ������
				x_test=(float)adcx*(3.3/4096);
				//}
			
			return  x_test;//����ֵ
		}



float Concentration_return(float k,float Vc0,float Vc) //��ʾADCֵ����
		{//
				
				float concetration;
					
				concetration=fabs((Vc-Vc0)/k);
			return  concetration;//����ֵ
		}




