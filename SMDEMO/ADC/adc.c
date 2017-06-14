 #include "adc.h"
 #include "delay.h"
 #include "stm32f10x_adc.h"
 #include "math.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//ADC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
		   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_1Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
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
//中位值法滤波 南京工程学院 严奎
u16	Get_Adc_Middle_value(u8 ch,u8 times)//times次数要小于15
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
		//for(count=1;count<times-1;count++)//去掉一个最高去掉一个最低 进行平均
			//sum += value_buf[count];
		//return (char)(sum/(N-2));
		return value_buf[(times-1)/2];
	}

//
u16	Get_Adc_Middle_Average(u8 ch,u8 times)//times次数要小于15
	{
		u32 value_buf[15],temp,sum;
		u8 count,i,j;
		count=times;
		for ( count=0;count<times;count++)
			{
			value_buf[count] = Get_Adc(ch);
				;//延时
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
		
		for(count=1;count<times-1;count++)//去掉一个最高去掉一个最低 进行平均
		{
			sum += value_buf[count];
		}
		return (sum/(times-2));
		//return value_buf[(times-1)/2];
	}


//float to strings
	

		// 浮点数转换成字符串
// 参数：data
// 返回：str
char  *Float_to_string(float data)
{	static char str[20];
		long i,j,k,temp,x;
		char intpart[20], dotpart[20];  // 数的整数部分和小数部分

		//1.确定符号位
		if(data<0) {str[0]='-';data=-data;}
		else str[0]=' ';

		//2.确定整数部分
		temp=(long)data;//去掉了小数部分
		//data=data-temp;//data 只剩下小数部分

		i=0;
		x=temp/10;
		while(x!=0)//??w为什么要精度那么高
			{
				intpart[i]=temp-10*x+48; //to ascii code
				temp=x;
				x=temp/10;
				i++;
			}
		intpart[i]=temp+48;

		//3.确定小数部分,取了12位小数
		data=data-(long)data;
		for(j=0;j<4;j++)//显示的位数
			{
				dotpart[j]=(int)(data*10)+48;
				data=data*10.0;
				data=data-(long)data;
			}

		//4.数据组装
		for(k=1;k<=i+1;k++) str[k]=intpart[i+1-k];
		str[i+2]='.';
		for(k=i+3;k<i+j+3;k++) str[k]=dotpart[k-i-3];
		str[i+j+3]=0x0D;
		//str[]="";
		
		return str;

}





float ADCvalue_test() //显示ADC值次数
		{//
				u16 adcx;//,datastoreOri_3[400];
				float x_test;
			  //for(i=0;i<3;i++){
				adcx=Get_Adc_Middle_value(ADC_Channel_1,15);//可以提高平均次数
				x_test=(float)adcx*(3.3/4096);
				//}
			
			return  x_test;//返回值
		}




float ADCvalue_test_parameter() //显示ADC值次数
		{//
				u16 adcx;//,datastoreOri_3[400];
				float x_test;
			  //for(i=0;i<3;i++){
				adcx=Get_Adc_Middle_value(ADC_Channel_1,15);//可以提高平均次数
				x_test=(float)adcx*(3.3/4096);
				//}
			
			return  x_test;//返回值
		}



float Concentration_return(float k,float Vc0,float Vc) //显示ADC值次数
		{//
				
				float concetration;
					
				concetration=fabs((Vc-Vc0)/k);
			return  concetration;//返回值
		}




