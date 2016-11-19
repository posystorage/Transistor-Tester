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


#define Meter_X1_pin 0
#define Meter_X2_pin 1
#define Meter_X3_pin 2
#define Meter_VX_pin 3

#define Meter_Y1_pin 4
#define Meter_Y2_pin 5
#define Meter_Y3_pin 6
#define Meter_VY_pin 7

#define Meter_Z1_pin 8
#define Meter_Z2_pin 9
#define Meter_Z3_pin 10
#define Meter_VZ_pin 11



void Meter_GPIO_Init(void);
void RST_meter_pin(void);
void SET_Pin(uint8_t pin,uint8_t state);//pin为对应脚位，state为状态，0为推挽低，1为推挽高，2为高阻

#define PinX	0
#define PinY	1
#define PinZ	2

#endif
