
#include "tm4c123gh6pm.h"

void delay_micro(int n);
void delay_milli(int n);
void LCD_PORT_INIT();
void LCD_FULL_INIT();
void LCD_COM(unsigned char a);
void LCD_DATA(unsigned char a);

void LCD_DATA(unsigned char a)
{
	GPIO_PORTB_DATA_R&=~0xE0;
	GPIO_PORTB_DATA_R|=0x20;
	GPIO_PORTA_DATA_R=a;
	GPIO_PORTB_DATA_R|=0x80;
	delay_micro(0);
		GPIO_PORTB_DATA_R&=~0xE0;
}

void LCD_COM(unsigned char a)
{
	GPIO_PORTB_DATA_R&=~0xE0;
	GPIO_PORTA_DATA_R=a;
	GPIO_PORTB_DATA_R|=0x80;
	delay_micro(0);
		GPIO_PORTB_DATA_R&=~0xE0;
	if(a <4) delay_milli(2); else delay_micro(37);
}
void LCD_PORT_INIT()
{
	SYSCTL_RCGCGPIO_R|=0x03;
	 while((SYSCTL_RCGCGPIO_R&0X03)==0)
	SYSCTL_PRGPIO_R|=0x03;
	GPIO_PORTA_DIR_R|=0xFF;
	GPIO_PORTA_DEN_R|=0xFF;
	GPIO_PORTA_AMSEL_R&= ~0XFF;
  GPIO_PORTA_AFSEL_R&= ~0XFF;
  GPIO_PORTA_PCTL_R&=~0xFFFFFFFF;
	GPIO_PORTB_DIR_R|=0xE0;
	GPIO_PORTB_DEN_R|=0xE0;
  GPIO_PORTB_AMSEL_R&= ~0XFF;
  GPIO_PORTB_AFSEL_R&= ~0XFF;
	GPIO_PORTB_PCTL_R&=~0xFFF00000; 
 }
	 
  void LCD_FULL_INIT()
	{
		LCD_PORT_INIT();
		LCD_COM(0x30);
		LCD_COM(0x06);
    LCD_COM(0x01);
    LCD_COM(0x0F);
	}
	void delay_milli(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3180;j++)
{}
}
void delay_micro(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3;j++)
{}
}	