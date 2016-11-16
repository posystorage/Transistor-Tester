#include "lcdgpio.h"        
#include "stm32f10x_gpio.h"

void MCUGPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
  
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//����SWD��ʧ��JTAG
	
  GPIO_InitStructure.GPIO_Pin =0xff00  ;	//��8λ		
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(DataPort, &GPIO_InitStructure);				 // ѡ��A�˿�
	
  GPIO_InitStructure.GPIO_Pin = RS_pin|CS_pin|BG_LIGHT_pin ;		
  GPIO_Init(ControlBPort, &GPIO_InitStructure);				 // ѡ��B�˿�
	//GPIO_SetBits(GPIOB,GPIO_Pin_6); 	
	//GPIO_ResetBits(GPIOB,GPIO_Pin_5); 

	GPIO_InitStructure.GPIO_Pin = rd_pin;		
  GPIO_Init(ControlCPort, &GPIO_InitStructure);				 // ѡ��C�˿�	
	
	
}

void LCD_write_8bit_dat(uint16_t dat)
{
	DataPort->ODR &= 0x00ff;
	DataPort->ODR |= ((dat<<8) & 0xff00);
}







