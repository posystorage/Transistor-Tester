#include "ADC.h"
uint32_t ADC_Dat[8];
uint32_t ADC_Vol_Dat[8];


void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
                    
	GPIO_InitStructure.GPIO_Pin = VIN_BAT|VIN_X1|VIN_X2|VIN_VREF|VIN_Y1|VIN_Y2|VIN_Z1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = VIN_Z2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

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
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_7Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ7.5����	  			    
  
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
	ADC_Vol_Dat[0]=ADC_Dat[0]*Reference_Vol*2/ADC_Dat[3];//��ص�ѹ
	ADC_Vol_Dat[1]=ADC_Dat[1]*Reference_Vol/ADC_Dat[3];//x1
	ADC_Vol_Dat[2]=ADC_Dat[2]*Reference_Vol/ADC_Dat[3];//x2
	ADC_Vol_Dat[3]=4096*Reference_Vol/ADC_Dat[3];//ϵͳ��ѹ
	ADC_Vol_Dat[4]=ADC_Dat[4]*Reference_Vol/ADC_Dat[3];//y1
	ADC_Vol_Dat[5]=ADC_Dat[5]*Reference_Vol/ADC_Dat[3];//y2
	ADC_Vol_Dat[6]=ADC_Dat[6]*Reference_Vol/ADC_Dat[3];//z1
	ADC_Vol_Dat[7]=ADC_Dat[7]*Reference_Vol/ADC_Dat[3];//z2
}
