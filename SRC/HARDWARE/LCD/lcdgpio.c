#include "lcdgpio.h"        
#include "stm32f10x_gpio.h"

void MCUGPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOD , ENABLE  );
  
  GPIO_InitStructure.GPIO_Pin =0xff00  ;	//高8位		
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(DataPort, &GPIO_InitStructure);				 // 选择A端口
	
  GPIO_InitStructure.GPIO_Pin = CS_pin ;		
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(ControlBPort, &GPIO_InitStructure);				 // 选择B端口	

	GPIO_InitStructure.GPIO_Pin = RST_pin|RS_pin|rd_pin|wr_pin  ;		
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(ControlCPort, &GPIO_InitStructure);				 // 选择C端口	
	TSF8H_DAT_WR_CLR;
}

void LCD_write_8bit_dat(uint16_t dat)
{
	DataPort->ODR &= 0x00ff;
	DataPort->ODR |= (uint16_t)((dat<<8) & 0x00ff);
}

uint16_t LCD_read_8bit_dat(void)//实际是返回低8位
{
	uint16_t dat;
	dat=GPIO_ReadInputData(DataPort);
	dat&=0x00ff;
	return dat;
}

void LCD_gpio2IPU(void)
{
DataPort->CRL=0X88888888; //PB0-7  上拉输入
}

void LCD_gpio2OutPP(void)
{
	DataPort->CRL=0X33333333; 		//PB0-7  上拉输出
}






