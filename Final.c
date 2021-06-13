//1
#include "final.h"

void UART5_Init()
{
SYSCTL_RCGCUART_R |= 0x20;
SYSCTL_RCGCGPIO_R |= 0x10;
	UART5_CTL_R &= 0x10;
	UART5_IBRD_R = 104;
	UART5_FBRD_R = 11;
	UART5_LCRH_R = 0x0070;
	UART5_CTL_R |= 0x0301;
  
	GPIO_PORTE_AFSEL_R |= 0x30;	
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF)+0x00110000;
	GPIO_PORTE_DEN_R |=0x30;
	GPIO_PORTE_AMSEL_R &= ~0x30; 
}

uint8_t UART5_Available(void){
	return ((UART5_FR_R&0x10) != 0) ? 0 : 1;
}

void uart5_write(uint8_t data){
   while((UART5_FR_R & UART_FR_TXFF) != 0){};
    UART0_DR_R = data;
}
//2
//3

//4
void CLK(){
      // ENABLE CLOCK FOR PORT A , B , F
   SYSCTL_RCGCGPIO_R |=  0x23;
     while((SYSCTL_PRGPIO_R & 0x23) == 0){};    // Wait until clock is stable
}

void PORTF_INIT(){
     // PORT F INITIALIZATION for RED LED
     GPIO_PORTF_LOCK_R = UNLOCK_PORT;           // Unlock PORTF
     GPIO_PORTF_CR_R |= 0x02;                   // Allow changes to PF1 (RED COLOR)
     GPIO_PORTF_AMSEL_R &= ~0x02;               // Disable analog for PF1
     GPIO_PORTF_AFSEL_R &= ~0x02;               // Disable alternate function for PF1
     GPIO_PORTF_PCTL_R &= ~0X000000F0;          // Select GPIO functionality
     GPIO_PORTF_DIR_R |= 0x02;                  // Set direction of PF1 as output
     GPIO_PORTF_DEN_R |= 0x02;                  // Enable digital in PF1
}

void LED_Output(unsigned char out) {
    GPIO_PORTF_DATA_R |= out;
}
void TARGET(){
    if (Dis >= 100){
            LED_Output(0x02);                      // IF DISTANCE HIGHER THAN 100 , RED LED WILL TURN ON.
  }
}

// Function for Converting from degrees to radian
long double Deg_Rad(long double deg){
    return (deg * PI / 180);
}

// Measuring the distance by longitude and latitude
long double Total_Distance(long double long1,long double long2,long double lat1,long double lat2) {
 long double dlong = Deg_Rad(long2 - long1);
 long double dlat = Deg_Rad(lat2 - lat1);
 long double phi1 = Deg_Rad(lat1);
 long double phi2 = Deg_Rad(lat2);
    // Haversine formula
  long double a = pow(sin((0.5 * dlat)), 2) + cos(phi1) * cos(phi2) * pow(sin((0.5 * dlong)), 2);
  long double d = 2 * R * asin(sqrt(a));
   Dis = Dis + d;
   return Dis;
}

void LCD_DATA(unsigned char data)
{
    GPIO_PORTA_DATA_R|=0x20;           // RS=1
    GPIO_PORTB_DATA_R=data;
    GPIO_PORTA_DATA_R|=0x80;           // EN = HIGH
    D_MICRO(0);
    GPIO_PORTA_DATA_R=0x00;            // EN = LOW
}

void LCD_COM(unsigned char com)
{
    GPIO_PORTA_DATA_R=0x00;             // RS=0 RW=0 EN=LOW
    GPIO_PORTB_DATA_R=com;
    GPIO_PORTA_DATA_R=0x80;             // EN = HIGH
    D_MICRO(0);
    GPIO_PORTA_DATA_R=0x00;
    if(com <4) D_MILLI(2); else D_MICRO(37);
}
//5
void LCD_init_PORT()
{
    // PORT B INITIALIZATION FOR OUTPUT
    GPIO_PORTB_DIR_R|=0xFF;              // SET DIRECTION AS OUTPUT
    GPIO_PORTB_DEN_R|=0xFF;              // ENABLE DIGITAL
    GPIO_PORTB_AMSEL_R&= ~0XFF;          // DISABLE ANALOG
    GPIO_PORTB_AFSEL_R&= ~0XFF;          // DISABLE ALTERNATE FUNCTION SELECTION
    GPIO_PORTB_PCTL_R&=~0xFFFFFFFF;      // SELECT GPIO FUNCTIONALITY
    // PORT A INITIALIZATION FOR LCD CONTROL  (PA5--> RS , PA6 ---> RW , PA7 --> EN)
    GPIO_PORTA_DIR_R|=0xE0;              // PA5 , PA6 , P7 DIRECTION AS OUTPUT
    GPIO_PORTA_DEN_R|=0xE0;              // ENABLE DIGITAL
    GPIO_PORTA_AMSEL_R&= ~0XE0;          // DISABLE ANALOG
    GPIO_PORTA_AFSEL_R&= ~0XE0;          // DISABLE ALTERNATE FUNCTION SELECTION
    GPIO_PORTA_PCTL_R&=~0xFFF00000;      // SELECT GPIO FUNCTIONALITY
    D_MICRO(37);
    // LCD COMMANDS
    LCD_COM(0x38);         // FOR 8-BITS 2 LINES IN LCD
    D_MICRO(37);
    LCD_COM(0x06);         // FOR CURSOR INCREMENT
    D_MICRO(37);
    LCD_COM(0x01);         // CLEAR DISPLAY
    D_MICRO(37);
    LCD_COM(0x0F);         // LCD ON ,cursor ON
    D_MICRO(37);
    LCD_COM(0x30);         // WAKE UP
    D_MICRO(37);
}

void D_MICRO(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3;j++)
{}
}

void D_MILLI(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3180;j++)
{}
}
void LCD_printS(char *s){
    int i;
	int Size = strlen(s);
    for(i=0;i<Size;i++){
        LCD_DATA(s[i]);
        D_MILLI(20);
    }
}


void LCD_showword(void)
{
    int i;
    char input[9]="distance=";

    for (i = 0 ; i<9 ;i++)
    {
        LCD_DATA(input[i]);
        D_MILLI(20);
    }
}

//6


























