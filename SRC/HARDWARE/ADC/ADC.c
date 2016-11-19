#include "ADC.h"
uint32_t ADC_Dat[8];
uint32_t ADC_Vol_Dat[8];


void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
                    
	GPIO_InitStructure.GPIO_Pin = VIN_BAT|VIN_X1|VIN_X2|VIN_VREF|VIN_Y1|VIN_Y2|VIN_Z1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = VIN_Z2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

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
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_7Cycles5 );	//ADC1,ADC通道,采样时间为7.5周期	  			    
  
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
		delay_us(50);
	}
	return temp_val/times;
} 

void Get_All_ADC_DAT(void)
{
	u8 i;
	for(i=0;i<8;i++)ADC_Dat[i]=0;
	for(i=0;i<Sample_Times;i++)
	{
		ADC_Dat[0]+=Get_Adc(VIN_BAT_CH);
		ADC_Dat[1]+=Get_Adc(VIN_X1_CH);
		ADC_Dat[2]+=Get_Adc(VIN_X2_CH);
		ADC_Dat[3]+=Get_Adc(VIN_VREF_CH);
		ADC_Dat[4]+=Get_Adc(VIN_Y1_CH);
		ADC_Dat[5]+=Get_Adc(VIN_Y2_CH);
		ADC_Dat[6]+=Get_Adc(VIN_Z1_CH);
		ADC_Dat[7]+=Get_Adc(VIN_Z2_CH);
	}
	for(i=0;i<8;i++)ADC_Dat[i]/=Sample_Times;
	ADC_Vol_Dat[0]=ADC_Dat[0]*Reference_Vol*2/ADC_Dat[3];//电池电压
	ADC_Vol_Dat[1]=ADC_Dat[1]*Reference_Vol/ADC_Dat[3];//x1
	ADC_Vol_Dat[2]=ADC_Dat[2]*Reference_Vol/ADC_Dat[3];//x2
	ADC_Vol_Dat[3]=4096*Reference_Vol/ADC_Dat[3];//系统电压
	ADC_Vol_Dat[4]=ADC_Dat[4]*Reference_Vol/ADC_Dat[3];//y1
	ADC_Vol_Dat[5]=ADC_Dat[5]*Reference_Vol/ADC_Dat[3];//y2
	ADC_Vol_Dat[6]=ADC_Dat[6]*Reference_Vol/ADC_Dat[3];//z1
	ADC_Vol_Dat[7]=ADC_Dat[7]*Reference_Vol/ADC_Dat[3];//z2
}
