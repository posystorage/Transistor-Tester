#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"
#include "delay.h"

#include "IO.h"

#define Reference_Vol 2490
#define Sample_Times 16

//GPIOA
#define VIN_BAT GPIO_Pin_0
#define VIN_X1 GPIO_Pin_1
#define VIN_X2 GPIO_Pin_2
#define VIN_VREF GPIO_Pin_3
#define VIN_Y1 GPIO_Pin_5
#define VIN_Y2 GPIO_Pin_6
#define VIN_Z1 GPIO_Pin_7
//GPIOB
#define VIN_Z2 GPIO_Pin_0


#define VIN_BAT_CH 0
#define VIN_X1_CH 1
#define VIN_X2_CH 2
#define VIN_VREF_CH 3
#define VIN_Y1_CH 5
#define VIN_Y2_CH 6
#define VIN_Z1_CH 7
#define VIN_Z2_CH 8

void  Adc_Init(void);
u16 Get_Adc_Average(u8 ch,u8 times);
void Get_All_ADC_DAT(void);

#endif
