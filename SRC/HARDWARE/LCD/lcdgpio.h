#ifndef __LCDGPIO_H
#define __LCDGPIO_H
#include "stdint.h"
#include "sys.h"
//�ֱ�����128x128,�������ڵĳ����õ���132x132
//LCD_1				����
//LCD_2				leda(+)
//LCD_3				ledk(-)
//LCD_4				vss
//LCD_5 6	    vdd
//LCD_7 8			����
//LCD_9				RST
//LCD_10			RS
//LCD_11			WR�ӵ͵�ƽ
//LCD_12			rd
//LCD_13-20		GPIOA��8λ
//LCD_21-28		����
//LCD_29			MPU�Ӹߵ�ƽ
//LCD_30			cs
//LCD_31			vss
//LCD_32			����

#define DataPort  GPIOB					//GPIOA��8λ//LCD_13-20

#define ControlBPort  GPIOB
//MPU�Ӹߵ�ƽ//LCD_29
#define CS_pin            GPIO_Pin_5//LCD_30
#define RS_pin            GPIO_Pin_4//LCD_10
#define BG_LIGHT_pin      GPIO_Pin_6

#define ControlCPort  GPIOA
#define rd_pin             GPIO_Pin_15//LCD_12


#define  TSF8H_STB_CS_SET     GPIO_SetBits(ControlBPort, CS_pin  )		
#define  TSF8H_STB_CS_CLR     GPIO_ResetBits(ControlBPort, CS_pin  )	 
#define  TSF8H_CLK_RS_SET     GPIO_SetBits(ControlBPort, RS_pin )		
#define  TSF8H_CLK_RS_CLR     GPIO_ResetBits(ControlBPort, RS_pin )	 
#define  TSF8H_DAT_EC_SET     GPIO_SetBits(ControlCPort, rd_pin)		
#define  TSF8H_DAT_EC_CLR     GPIO_ResetBits(ControlCPort, rd_pin)
#define  TSF8H_BG_LGT_SET     GPIO_SetBits(ControlBPort, BG_LIGHT_pin)

void MCUGPIO_Init(void);
void LCD_write_8bit_dat(uint16_t dat);


#endif

