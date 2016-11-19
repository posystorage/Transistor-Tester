#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "lcdgpio.h"
#include "usart.h"
#include "IO.h"
#include "ADC.h"


#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"


extern uint32_t ADC_Dat[8];
extern uint32_t ADC_Vol_Dat[8];

int main(void)
{ 
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	MCUGPIO_Init();
	Adc_Init();
	delay_ms(200);	
	TSF8H_init();
	Meter_GPIO_Init();
		
	USB_Port_Set(0); 	//USB先断开
	delay_ms(100);
	USB_Port_Set(1);	//USB再次连接
 	Set_USBClock();   
 	USB_Interrupts_Config();    
 	USB_Init();	
	

	
	while(1)
	{
		USB_USART_SendData(0x5a);
		
		LCD_ShowStr(0,0,"ADC1",16,BLUE2);
		LCD_ShowStr(0,16,"ADC2",16,BLUE2);
		LCD_ShowStr(0,32,"ADC3",16,BLUE2);
		LCD_ShowStr(0,48,"ADC4",16,BLUE2);
		LCD_ShowStr(0,64,"ADC5",16,BLUE2);
		LCD_ShowStr(0,80,"ADC6",16,BLUE2);
		LCD_ShowStr(0,96,"ADC7",16,BLUE2);
		LCD_ShowStr(0,112,"ADC8",16,BLUE2);
		Get_All_ADC_DAT();
		LCD_ShowNum(32,0,ADC_Dat[0],5,16,WHITE);
		LCD_ShowNum(32,16,ADC_Dat[1],5,16,WHITE);
		LCD_ShowNum(32,32,ADC_Dat[2],5,16,WHITE);
		LCD_ShowNum(32,48,ADC_Dat[3],5,16,WHITE);
		LCD_ShowNum(32,64,ADC_Dat[4],5,16,WHITE);
		LCD_ShowNum(32,80,ADC_Dat[5],5,16,WHITE);
		LCD_ShowNum(32,96,ADC_Dat[6],5,16,WHITE);
		LCD_ShowNum(32,112,ADC_Dat[7],5,16,WHITE);
		
		LCD_ShowNum(80,0,ADC_Vol_Dat[0],5,16,WHITE);
		LCD_ShowNum(80,16,ADC_Vol_Dat[1],5,16,WHITE);
		LCD_ShowNum(80,32,ADC_Vol_Dat[2],5,16,WHITE);
		LCD_ShowNum(80,48,ADC_Vol_Dat[3],5,16,WHITE);
		LCD_ShowNum(80,64,ADC_Vol_Dat[4],5,16,WHITE);
		LCD_ShowNum(80,80,ADC_Vol_Dat[5],5,16,WHITE);
		LCD_ShowNum(80,96,ADC_Vol_Dat[6],5,16,WHITE);
		LCD_ShowNum(80,112,ADC_Vol_Dat[7],5,16,WHITE);		
		
		delay_ms(200);//delay 1s
	}
}


