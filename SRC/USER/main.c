#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "lcdgpio.h"
#include "usart.h"


#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"

int main(void)
{ 
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	MCUGPIO_Init();
	delay_ms(200);	
	TSF8H_init();
		
	USB_Port_Set(0); 	//USB先断开
	delay_ms(100);
	USB_Port_Set(1);	//USB再次连接
 	Set_USBClock();   
 	USB_Interrupts_Config();    
 	USB_Init();	
	

	while(1)
	{
		USB_USART_SendData(0x5a);
		TSF8H_clr(BLACK);
		LCD_ShowStr(25,2,"LCD TEST",16,RED);
    delay_ms(1000);
		LCD_ShowStr(15,20,"stm32f103",16,GREEN);
		LCD_ShowStr(0,36,"Transistor-Tester",16,MAGENTA);		
    delay_ms(1000);
		LCD_ShowStr(5,70,"by:",16,WHITE);		
		LCD_ShowStr(35,70,"2545889167",16,YELLOW);
		LCD_ShowStr(40,86,"mydigit",16,BLUE2);
		delay_ms(1000);//delay 1s
		TSF8H_clr(BLACK);
		LCD_DrawLine(0, 0, 15, 20,RED);
		LCD_DrawRectangle(20, 20, 35, 30,GREEN);
		LCD_Draw_Circle(50,50,13,BLUE);
		delay_ms(1000);//delay 1s
	}
}


