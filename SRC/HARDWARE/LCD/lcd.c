#include "lcd.h"
#include "lcdgpio.h"
#include "delay.h"
#include "font.h" 
#include "stm32f10x_gpio.h"



void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}



void TSF8H_wcmd(unsigned char cmd)
{
	TSF8H_STB_CS_CLR;
	LCD_write_8bit_dat(cmd);
	//GPIOA->ODR=cmd;
	TSF8H_CLK_RS_CLR;//rs=0=cmd
	TSF8H_DAT_EC_SET;
	//Delay(10);
	TSF8H_DAT_EC_CLR;//EC 's fall edge enable LCM input
	//Delay(10);
	TSF8H_STB_CS_SET;//CS =1,dis-chose LCM
}
void TSF8H_wdat(unsigned char dat)
{
	TSF8H_STB_CS_CLR;
	LCD_write_8bit_dat(dat);
	//GPIOA->ODR=dat;
	TSF8H_CLK_RS_SET;//rs=1=dat
	TSF8H_DAT_EC_SET;
	//Delay(10);
	TSF8H_DAT_EC_CLR;//EC 's fall edge enable LCM input
	//Delay(10);
	TSF8H_STB_CS_SET;//CS =1,dis-chose LCM
}
void TSF8H_set_contrast(unsigned int dat)
{
	TSF8H_wcmd(0x2a);//R_CONTRAST_CONTROL1
	TSF8H_wcmd(dat);//0-255
}

void TSF8H_init(void)
{
	delay_ms(100);//delay 100ms
	//standby mode off
	TSF8H_wcmd(0x2c);
	delay_ms(20);//delay 20ms
	//OSC ON
	TSF8H_wcmd(0x02);
	TSF8H_wcmd(0x01);//enable Internal OSC and use it
	delay_ms(20);//delay 20ms
	//DCDC1 ON
	TSF8H_wcmd(0x26);
	TSF8H_wcmd(0x01);
	delay_ms(20);//delay 20ms
	//AMP ON
	TSF8H_wcmd(0x26);
	TSF8H_wcmd(0x09);
	delay_ms(20);//delay 20ms
	//DCDC2 ON
	TSF8H_wcmd(0x26);
	TSF8H_wcmd(0x0b);
	delay_ms(20);//delay 20ms
	//DCDC3 ON
	TSF8H_wcmd(0x26);
	TSF8H_wcmd(0x0f);
	delay_ms(20);//delay 20ms
	
	//set all other 
	 TSF8H_wcmd(0x20);//R_DCDC_Select
	 TSF8H_wcmd(0x01);
	 //b0=DC(1)=normal mode DC step up =0=1.0x =1=1.5x   
	 //b2=DC(2)=partial mode step up =0=1.0x =1=1.5x
	 TSF8H_wcmd(0x28);//R_TEMP_COMPENSATION
	 TSF8H_wcmd(0x01);
	 TSF8H_wcmd(0x10);//R_DRIVER_OUTPUT_MODE
	 TSF8H_wcmd(0x0B);
	 //b5b4=DLN=set duty =00=1/132 =01=1/104 =10=1/80 =11=1/96
	 //b3=MY    =0=row address++  =1=row address--
	 //b2=MX    =0=column address++  =1=column address--
	 //b1=SWP   SEGAi?SEGCi??????
	 //b0=CDIR  COM?????????
	 TSF8H_wcmd(0x40);//R_ENTRY_MODE
	 TSF8H_wcmd(0x81);
	 //b7=16B=bus wide  =0=16bit =1=8bit
	 //b2=MDI =0
	 //b1=Y/X  =0=column address count first  =1=row address count first
	 //b0=RMW  =0
	 TSF8H_wcmd(0x34);//R_N_LINE_INVERSION  N-block inversion Set (34H)
	 TSF8H_wcmd(0x04);
	 //TSF8H_wcmd(0xfa);//?????
	 //TSF8H_wcmd(0x5f);//?????
	 TSF8H_set_contrast(0xda);
	 TSF8H_wcmd(0x53);//R_SPEC_DISPLAY_PATTERN
	 TSF8H_wcmd(0x00);
	 //b1b0=SDP =00=normal mode =01=reverse display =10=whole display pattern OFF =11=whole display pattern ON
	 TSF8H_wcmd(0x30);//R_ADDRESSING_MODE
	 TSF8H_wcmd(0x00);
	 //b7=FIR
	 //b5=GSM =0=65K color =1=4K
	 //b4=DSG : Duty Adjust Setting
	 //b3=SGF : Sub Group Frame Inversion mode setting
	 //b1=SGP : Sub Group Phase mode setting
	 TSF8H_wcmd(0x55);//R_PARTIAL_DISPLAY_MODE
	 TSF8H_wcmd(0x00);
	 //b2=PT: Partial Display ON/OFF =0=normal mode =1=Partial display ON
	 //b1=PDM: Partial Display mode set
	 //b0=PDTY: Duty selection
	 TSF8H_wcmd(0x42);//R_X_ADDR_AREA
	 TSF8H_wcmd(0x00);
	 //Y start address set (Initial Status = 00H)
	 TSF8H_wcmd(0x83);
	 //Y end address set (Initial Status = 83H)
	 TSF8H_wcmd(0x43);//R_Y_ADDR_AREA
	 TSF8H_wcmd(0x00);
	 //X start address set (Initial Status = 00H)
	 TSF8H_wcmd(0x83);
	 //X end address set (Initial Status = 83H)
	 TSF8H_wcmd(0x53);//R_SPEC_DISPLAY_PATTERN
	 TSF8H_wcmd(0x00);	
	 //b1b0=SDP =00=normal mode =01=reverse display =10=whole display pattern OFF =11=whole display pattern ON
	 delay_ms(300);//delay 300ms
	//display on
	TSF8H_wcmd(0x51);//R_DISPLAY_ON
	
	TSF8H_clr(BLACK);
	
	TSF8H_BG_LGT_SET;//开背光

}

void Set_show_windows(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)//设置显示窗口
{
 	  TSF8H_wcmd(0x42);  //column
	  TSF8H_wcmd(x1);  
    TSF8H_wcmd(x2);
	
		TSF8H_wcmd(0x43);
		TSF8H_wcmd(y1); 
    TSF8H_wcmd(y2);
}
void Set_Position(uint8_t x,uint8_t y)//设置起始位置
{
	 	TSF8H_wcmd(0x42);  //column
	  TSF8H_wcmd(x);  
    TSF8H_wcmd(0x83);
	
		TSF8H_wcmd(0x43);
		TSF8H_wcmd(y); 
    TSF8H_wcmd(0x83);
}



void LCD_Write_uint16(uint16_t Data)
{
		TSF8H_wdat(((unsigned char *)&Data)[1]);
		TSF8H_wdat(((unsigned char *)&Data)[0]);
}


void TSF8H_clr(unsigned int color)
{
	unsigned int i;
	Set_Position(0,0);
	for(i=((132*132));i>0;i--)
	{
		TSF8H_wdat(((unsigned char *)&color)[1]);
		TSF8H_wdat(((unsigned char *)&color)[0]);
	}
}


void Display_Point(uint8_t x,uint8_t y,uint16_t Color)//在任意位置画点
{
 	Set_Position(x,y);
	LCD_Write_uint16(Color);

}


//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		Display_Point(uRow,uCol,color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}

void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		Display_Point(x0+a,y0-b,color);             //5
 		Display_Point(x0+b,y0-a,color);             //0           
		Display_Point(x0+b,y0+a,color);             //4               
		Display_Point(x0+a,y0+b,color);             //6 
		Display_Point(x0-a,y0+b,color);             //1       
 		Display_Point(x0-b,y0+a,color);             
		Display_Point(x0-a,y0-b,color);             //2             
  	Display_Point(x0-b,y0-a,color);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 



//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
//void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode,uint16_t color)
//{  							  
//    uint8_t temp,t1,t;
//	uint16_t y0=y;
//	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
// 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
//	for(t=0;t<csize;t++)
//	{   
//		if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
//		else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
//		else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
//		else return;								//没有的字库
//		for(t1=0;t1<8;t1++)
//		{			    
//			if(temp&0x80)Display_Point(x,y,color);
//			else if(mode==0)Display_Point(x,y,BLACK);
//			temp<<=1;
//			y++;
//			if(y>=Height)return;		//超区域了
//			if((y-y0)==size)
//			{
//				y=y0;
//				x++;
//				if(x>=Width)return;	//超区域了
//				break;
//			}
//		}  	 
//	}  	    	   	 	  
//}

void quickly_dat(uint16_t dat)
{
	LCD_write_8bit_dat(((unsigned char *)&dat)[1]);
	TSF8H_DAT_EC_SET;
	TSF8H_DAT_EC_CLR;//EC 's fall edge enable LCM input
	LCD_write_8bit_dat(((unsigned char *)&dat)[0]);
	TSF8H_DAT_EC_SET;
	TSF8H_DAT_EC_CLR;//EC 's fall edge enable LCM input

}

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode,uint16_t color)
{
    uint8_t temp,t1,t;
 	num=num-' ';
 	switch(size)
 	{

 	case 12:
 		Set_show_windows(x,y,x+5,y+11);
 		TSF8H_STB_CS_CLR;
 		TSF8H_CLK_RS_SET;//rs=1=dat
 		for(t=0;t<12;t++)
 		{
 			temp=asc2_1206[num][t];
			for(t1=0;t1<6;t1++)
			{
				if(temp&0x80)quickly_dat(color);
				else if(mode==0)quickly_dat(BLACK);
				temp<<=1;
			}
 		}
 		TSF8H_STB_CS_SET;
 		break;
 	case 16:
 		Set_show_windows(x,y,x+7,y+15);
 		TSF8H_STB_CS_CLR;
 		TSF8H_CLK_RS_SET;//rs=1=dat
 		for(t=0;t<16;t++)
 		{
 			temp=asc2_1608[num][t];
			for(t1=0;t1<8;t1++)
			{
				if(temp&0x80)quickly_dat(color);
				else if(mode==0)quickly_dat(BLACK);
				temp<<=1;
			}
 		}
 		TSF8H_STB_CS_SET;
 		break;
 
 	default :break;
 	}
}


void LCD_ShowStr(uint16_t x,uint16_t y,uint8_t *str,uint8_t size,uint16_t Color)//显示字符串
{
   while(*str!='\0')
   {
		 LCD_ShowChar(x,y,*str,size,0,Color);
	 str++;
	 x+=(size/2);
	 if(x>=(Width-(size/2)))
	 {
	  x=0;
	  y+=size;
	 }
   }
}

//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(uint8_t m,uint8_t n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0,color);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0,color); 
	}
}
//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);	 
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode,uint16_t color)
{  
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01,color);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01,color);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01,color); 
	}
} 



void GetGBKCode_from_flash(unsigned short int* pBuffer,const unsigned char * c)
{ 
   
}

/* 显示一个汉字 
 * 大小为 16（宽度）* 16（高度），共32个字节
 * 取模顺序为：高位在前，低位在后
 */
void LCD_DispCH(uint16_t x, uint16_t y, const uint8_t *pstr, uint16_t color)
{
	uint8_t page , column;
	uint16_t buffer[16];		
	uint16_t tmp_char=0,tmp_char2=0;
	Set_show_windows(x,y,x+16-1,y+16-1);
	
	GetGBKCode_from_flash(buffer,pstr);	 /* 取字模数据 */
	
	for(page=0; page< 16; page++)
	{
    /* 取出两个字节的数据，在lcd上即是一个汉字的一行 */
		tmp_char=buffer[page]&0xff00;
		tmp_char2=buffer[page]&0x00ff;
		tmp_char>>=8;
		tmp_char2<<=8;
		tmp_char|=tmp_char2;
		for (column=0; column< 16; column++)
		{			
			if ( tmp_char & 0x8000 )  /* 高位在前 */
			{				
					TSF8H_wdat(((unsigned char *)&color)[1]);
					TSF8H_wdat(((unsigned char *)&color)[0]);
			}
			else
			{			
				TSF8H_wdat(0x00);
				TSF8H_wdat(0x00);
			}
			tmp_char <<= 1;
		}
	}
}

/*
 * 显示一串汉字
 */
void LCD_DispStrCH(uint16_t x, uint16_t y, const uint8_t *pstr, uint16_t color) 
{
	while( *pstr != '\0' )
	{
		if( x > (Width-16) )
		{
			x = 0;
			y += 16;
		}
		if( y > (Height-16) )
		{
			x = 0;
			y = 0;
		}		
		LCD_DispCH(x, y, pstr, color);
		pstr +=2;   /* 一个汉字两个字节 */  
		x += 16;		
	}	   
}


/* 
 * 中英文混合显示，不能显示中文标点符号  
 * 中文大小：16*16
 * 英文大小：12*6
 */
void LCD_DispEnCh(uint16_t x, uint16_t y, const uint8_t *pstr, uint16_t color)
{
	while(*pstr != '\0')
	{
		if(*pstr <= 126)		/* 字符串 */
		{
			if( x > (Width-8) )
			{
				x = 0;
				y += 16;
			}
			if( y > (Height-16) )
			{
				x = 0;
				y = 0;
			}
			LCD_ShowChar(x,y,*pstr,16,0,color);
			//LCD_DispChar(x, y, *pstr, color);
			x += 8;
			pstr++;
		}
		else	/* 汉字 */
		{
			if( x > (Width-16) )
			{
				x = 0;
				y += 16;
			}
			if( y > (Height-16) )
			{
				x = 0;
				y = 0;
			}		
			LCD_DispCH(x, y, pstr, color);
			pstr +=2;
			x += 16;
    }
  }
} 
