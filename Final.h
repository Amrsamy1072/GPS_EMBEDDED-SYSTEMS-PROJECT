#include "tm4c123gh6pm.h"
#include "stdint.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void SystemInit () {}
	// DEFINITIONS
#define UNLOCK_PORT 0x4C4F434B
#define PI 3.14159265
#define R 6371000

// INITIALIZE DISTANCE TO 100 TO TEST RED LED
long double Dis=0;
char array[60]={0};	


// FUNCTIONS
void CLK(void);
void PORTF_INIT(void);
void LED_Output(unsigned char out);
void TARGET(void);
long double Deg_Rad(long double deg);
long double Total_Distance(long double long1,long double long2,long double lat1,long double lat2);
void LCD_DATA(unsigned char data);
void LCD_COM(unsigned char com);
void LCD_init_PORT(void);
void D_MICRO(int n);
void D_MILLI(int n);
void LCD_showword(void);
void  getdata(void);
void UART5_Init(void);
uint8_t UART5_Available(void);
uint8_t UART5_Read(void);
bool GPS_stat(void);
void  getdata(void);
long double GpsToDecimalDegrees(const char* nmeaPos);
long double get_lat (void);
long double get_lon (void);
void LCD_printS(char *s);
