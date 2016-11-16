#ifndef __LCD_H
#define __LCD_H

#include "stdint.h"

#define Height 132
#define Width  128

#define RED    0xF800
#define GREEN  0x07E0
#define BLUE   0x001F
#define YELLOW 0xFFE0
#define WHITE  0xFFFF
#define BLACK  0x0000
#define GREY   0xF7DE	/* 灰色 */
#define BLUE2	 0x051F	/* 浅蓝色 */
#define MAGENTA      0xF81F	/* 红紫色，洋红色 */
#define CYAN   0x7FFF	/* 蓝绿色，青色 */



void TSF8H_init(void);
void TSF8H_clr(unsigned int color);
void Set_show_windows(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
void Set_Position(uint8_t x,uint8_t y);
void Display_Point(uint8_t x,uint8_t y,uint16_t Color);

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode,uint16_t color);
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color);
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode,uint16_t color);
void LCD_ShowStr(uint16_t x,uint16_t y,uint8_t *str,uint8_t size,uint16_t Color);//显示英文字符串
void LCD_DispCH(uint16_t x, uint16_t y, const uint8_t *pstr, uint16_t color);
void LCD_DispStrCH(uint16_t x, uint16_t y, const uint8_t *pstr, uint16_t color); 
void LCD_DispEnCh(uint16_t x, uint16_t y, const uint8_t *pstr, uint16_t color);
#endif

