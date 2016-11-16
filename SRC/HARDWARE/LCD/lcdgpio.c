#include "lcdgpio.h"        
#include "stm32f10x_gpio.h"

void MCUGPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
  
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//开启SWD，失能JTAG
	
  GPIO_InitStructure.GPIO_Pin =0xff00  ;	//高8位		
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(DataPort, &GPIO_InitStructure);				 // 选择A端口
	
  GPIO_InitStructure.GPIO_Pin = RS_pin|CS_pin|BG_LIGHT_pin ;		
  GPIO_Init(ControlBPort, &GPIO_InitStructure);				 // 选择B端口
	//GPIO_SetBits(GPIOB,GPIO_Pin_6); 	
	//GPIO_ResetBits(GPIOB,GPIO_Pin_5); 

	GPIO_InitStructure.GPIO_Pin = rd_pin;		
  GPIO_Init(ControlCPort, &GPIO_InitStructure);				 // 选择C端口	
	
	
}

void LCD_write_8bit_dat(uint16_t dat)
{
	DataPort->ODR &= 0x00ff;
	DataPort->ODR |= ((dat<<8) & 0xff00);
}







