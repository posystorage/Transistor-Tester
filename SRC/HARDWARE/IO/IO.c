#include "IO.h"
#include "ADC.h"

GPIO_TypeDef *ADC_GPIO_Port_Arrange[12] = {GPIOC, GPIOC, GPIOC, GPIOA,
																					 GPIOA, GPIOA, GPIOA, GPIOA,
																					 GPIOB, GPIOB, GPIOA, GPIOA
																					};

const uint16_t ADC_GPIO_Pin_Arrange[12] = {GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15, GPIO_Pin_1,
                                           GPIO_Pin_10, GPIO_Pin_4, GPIO_Pin_9, GPIO_Pin_5,
                                           GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_8, GPIO_Pin_7,
                                          };

const uint16_t ADC_GPIO_Pin_Arr_Num[12] = {13, 14, 15, 1,
                                           10, 4, 9, 5,
                                           1, 2, 8, 7,
                                          };


void Meter_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =Meter_IO_Y1|Meter_IO_Y2|Meter_IO_Y3|Meter_IO_Z3;	//高8位		
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;		   // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // 选择A端口

	GPIO_InitStructure.GPIO_Pin =Meter_IO_Z1|Meter_IO_Z2;	//高8位	
  GPIO_Init(GPIOB, &GPIO_InitStructure);				 // 选择B端口
	
	GPIO_InitStructure.GPIO_Pin =Meter_IO_X1|Meter_IO_X2|Meter_IO_X3;	//高8位	
  GPIO_Init(GPIOC, &GPIO_InitStructure);				 // 选择C端口	
}

void RST_meter_pin(void)
{
	u8 i;
	for(i=0;i<12;i++)
	{		
		if(i==3|i==7|i==11)
		{
			ADC_GPIO_Port_Arrange[i]->CRL&=~(0x0F<<(ADC_GPIO_Pin_Arr_Num[i]*4));	//ADC位的处理
		}
		else
		{
			if(ADC_GPIO_Pin_Arr_Num[i]>7)
			{
				ADC_GPIO_Port_Arrange[i]->CRH|=(0x0F<<(ADC_GPIO_Pin_Arr_Num[i]-8)*4);
				ADC_GPIO_Port_Arrange[i]->CRH&=~(0x0B<<((ADC_GPIO_Pin_Arr_Num[i]-8)*4));//高位			
			}
			else
			{
				ADC_GPIO_Port_Arrange[i]->CRL|=0x0F<<(ADC_GPIO_Pin_Arr_Num[i]*4);
				ADC_GPIO_Port_Arrange[i]->CRL&=~(0x0B<<(ADC_GPIO_Pin_Arr_Num[i]*4));//低位			
			}
		}
		ADC_GPIO_Port_Arrange[i]->BRR=ADC_GPIO_Pin_Arrange[i];	//清空	
	}
}

void SET_Pin(uint8_t pin,uint8_t state)//pin为对应脚位，state为状态，0为推挽低，1为推挽高，2为高阻
{
    switch(state)
    {
    case 0:
			
			if(ADC_GPIO_Pin_Arr_Num[pin]>7)
			{
				ADC_GPIO_Port_Arrange[pin]->CRH|=(0x0F<<(ADC_GPIO_Pin_Arr_Num[pin]-8)*4);
				ADC_GPIO_Port_Arrange[pin]->CRH&=~(0x03<<((ADC_GPIO_Pin_Arr_Num[pin]-8)*4+2));//高位			
			}
			else
			{
				ADC_GPIO_Port_Arrange[pin]->CRL|=0x0F<<(ADC_GPIO_Pin_Arr_Num[pin]*4);
				ADC_GPIO_Port_Arrange[pin]->CRL&=~(0x03<<(ADC_GPIO_Pin_Arr_Num[pin]*4+2));//低位			
			}			
			ADC_GPIO_Port_Arrange[pin]->BRR=ADC_GPIO_Pin_Arrange[pin];	//推挽低
        break;
    case 1:
			if(ADC_GPIO_Pin_Arr_Num[pin]>7)
			{
				ADC_GPIO_Port_Arrange[pin]->CRH|=(0x0F<<(ADC_GPIO_Pin_Arr_Num[pin]-8)*4);
				ADC_GPIO_Port_Arrange[pin]->CRH&=~(0x03<<((ADC_GPIO_Pin_Arr_Num[pin]-8)*4+2));//高位			
			}
			else
			{
				ADC_GPIO_Port_Arrange[pin]->CRL|=0x0F<<(ADC_GPIO_Pin_Arr_Num[pin]*4);
				ADC_GPIO_Port_Arrange[pin]->CRL&=~(0x03<<(ADC_GPIO_Pin_Arr_Num[pin]*4+2));//低位			
			}			
			ADC_GPIO_Port_Arrange[pin]->BSRR=ADC_GPIO_Pin_Arrange[pin];	//推挽高
        break;
    case 2:
			if(pin==3|pin==7|pin==11)
			{
				
				ADC_GPIO_Port_Arrange[pin]->CRL&=~(0x0F<<(ADC_GPIO_Pin_Arr_Num[pin]*4));	//ADC位的处理
			}
			else
			{
				if(ADC_GPIO_Pin_Arr_Num[pin]>7)
				{
					ADC_GPIO_Port_Arrange[pin]->CRH|=(0x0F<<(ADC_GPIO_Pin_Arr_Num[pin]-8)*4);
					ADC_GPIO_Port_Arrange[pin]->CRH&=~(0x0B<<((ADC_GPIO_Pin_Arr_Num[pin]-8)*4));//高位			
				}
				else
				{
					ADC_GPIO_Port_Arrange[pin]->CRL|=0x0F<<(ADC_GPIO_Pin_Arr_Num[pin]*4);
					ADC_GPIO_Port_Arrange[pin]->CRL&=~(0x0B<<(ADC_GPIO_Pin_Arr_Num[pin]*4));//低位			
				}
			}
			ADC_GPIO_Port_Arrange[pin]->BRR=ADC_GPIO_Pin_Arrange[pin];	//推挽低
        break;
    default:
        break;
    }
}
