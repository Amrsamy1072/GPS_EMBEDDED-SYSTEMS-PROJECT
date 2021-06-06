// Inclusions
#include "tm4c123gh6pm.h"
#include "math.h"
#include "stdint.h"

// DEFINITIONS
#define UNLOCK_PORT 0x4C4F434B
#define PI 3.14159265
#define R 6371000

// INITIALIZE DISTANCE TO 100 TO TEST RED LED
double Dis=100;

// Define SystemInit
void SystemInit(){}

// FUNCTIONS
void CLK(void);
void PORTF_INIT(void);
void LED_Output(unsigned char out);
void TARGET(void);
void uart(void);
char UART_Receiver(void);
double Deg_Rad(double deg);
double Total_Distance(double long1, double long2, double lat1, double lat2);
void LCD_DATA(unsigned char data);
void LCD_COM(unsigned char com);
void LCD_init_PORT(void);
void D_MICRO(int n);
void D_MILLI(int n);
void LCD_showdist(int value);
void LCD_showword(void);

