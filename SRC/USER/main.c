#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "lcdgpio.h"
#include "picture.h"
#include "usart.h"	
//中文字库显示暂不支持中文标点符号
//请先在以0x08040000为起始地址的位置烧录中文字库文件
//本程序仅限stm/gd32f103xE芯片使用，也就是说要求芯片flash容量为512k

int main(void)
{ 
	delay_init();
	MCUGPIO_Init();
	delay_ms(500);	
	TSF8H_init();
	TSF8H_dis_BMP(&gImage_333[0]);
	delay_ms(1000);

	while(1)
	{

		TSF8H_dis_BMP(&gImage_sccx[0]);
		delay_ms(1000);//delay 1s
		TSF8H_dis_BMP(&gImage_333[0]);
		delay_ms(1000);//delay 1s
		Display_Gray();
		delay_ms(1000);//delay 1s
		Display_RGB();
		delay_ms(1000);//delay 1s
		Display_FullColorline();
		delay_ms(1000);//delay 1s	
		TSF8H_clr(RED);
		delay_ms(1000);//delay 1s
		TSF8H_clr(GREEN);
		delay_ms(1000);//delay 1s
		TSF8H_clr(BLUE);
		delay_ms(1000);//delay 1s
		TSF8H_clr(YELLOW);
		delay_ms(1000);//delay 1s
		TSF8H_clr(WHITE);
		delay_ms(1000);//delay 1s
		TSF8H_clr(BLACK);
		delay_ms(1000);//delay 1s	
		//Display_Str(25,0,"LCD TEST",RED);
		LCD_ShowStr(25,2,"LCD TEST",16,RED);
    delay_ms(1000);
		LCD_ShowStr(15,20,"stm32 103/401",16,GREEN);
    LCD_DispEnCh(5,36,"核心板///撸黄群",GREEN);
		LCD_ShowStr(20,52,"299202988",16,MAGENTA);		
    delay_ms(1000);
		LCD_ShowStr(5,70,"by:",16,WHITE);		
		LCD_ShowStr(35,70,"2545889167",16,YELLOW);
		LCD_ShowStr(40,86,"mydigit",16,BLUE2);
		delay_ms(1000);
    LCD_ShowStr(20,110,"2016/07/30",16,BLUE);
		delay_ms(1000);//delay 1s
		TSF8H_clr(BLACK); 
		LCD_DispEnCh(0, 4, (uint8_t *)"你隐深山折枝柳  我倚舟间共和渔  相守相携的岁月  何患无旁及      我们依然会在白露中醒来          晚霜中挽手老去", CYAN);
		delay_ms(1000);//delay 1s
		TSF8H_clr(BLACK);
		LCD_DrawLine(0, 0, 15, 20,RED);
		LCD_DrawRectangle(20, 20, 35, 30,GREEN);
		LCD_Draw_Circle(50,50,13,BLUE);
		//LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode,uint16_t color)
		LCD_ShowChar(0,80,'A',24,0,YELLOW);
		//LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color)
		LCD_ShowNum(50,80,1234,4,12,WHITE);
		delay_ms(1000);//delay 1s
		delay_ms(1000);//delay 1s
	}
}


