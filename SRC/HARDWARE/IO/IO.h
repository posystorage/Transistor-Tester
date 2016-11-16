#ifndef __IO_H
#define __IO_H
#include "stm32f10x.h"

//GPIOA
#define Meter_IO_Y1	GPIO_Pin_10
#define Meter_IO_Y2 GPIO_Pin_4
#define Meter_IO_Y3 GPIO_Pin_9
#define Meter_IO_Z3 GPIO_Pin_8

//GPIOB
#define Meter_IO_Z1	GPIO_Pin_1
#define Meter_IO_Z2 GPIO_Pin_2

//GPIOC
#define Meter_IO_X1	GPIO_Pin_13
#define Meter_IO_X2 GPIO_Pin_14
#define Meter_IO_X3 GPIO_Pin_15


void Meter_GPIO_Init(void);



#endif
