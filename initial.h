#include "tm4c123gh6pm.h"
#include "math.h"
#include "stdint.h"
#define UNLOCK_PORT 0x4C4F434B
#define PI 3.14159265
#define R 6371000


void D_MICRO(int n);
void D_MILLI(int n);
void LCD_init_PORT(void);
void LCD_COM(unsigned char com);
void LCD_DATA(unsigned char data);
void CLK(void);
void LED_Output(unsigned char out);
void TARGET(void);
void SystemInit(){}
double Dis=100;       // INITIALIZE DISTANCE TO 100 TO TEST RED LED
void PORTF_INIT(void);
double Deg_Rad(double deg);
double Total_Distance(double long1, double long2, double lat1, double lat2);
void LCD_DIST(int num);
void LCD(void);

