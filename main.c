#include "initial.h"


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

//uart initilization
void uart(void){
	SYSCTL_RCGCUART_R |= 0x04;     //activate UART2
	SYSCTL_RCGCGPIO_R |= 0x08;     //activate PORTD
	UART2_CTL_R &= ~0x01;         //disable the UART
	
	//BaudRate = 9600 --> 16MHZ /(16*9600) = 104.1667
	UART2_IBRD_R = 104;              //integer part = 104
	UART2_FBRD_R = 11;              //fractional part = 0.1667*64 = 11
	UART2_LCRH_R = 0x70;            //8-bit data, no parity, one stop, FIFo.s enabled
	UART2_CTL_R |= 0x01;	       //enable the UART
	UART2_CTL_R |= 0x200;          //to make uart receiver
	
	GPIO_PORTD_LOCK_R = UNLOCK_PORT;        // Unlock PORT D
	GPIO_PORTD_CR_R |= 0xC0;                // Allow changes to PD6 , PD7
	GPIO_PORTD_AFSEL_R |= 0xC0;             //enable alternate function for PD6 & PD7
	GPIO_PORTD_DEN_R |= 0xC0;               // PD6 & PD7 as digital I/O
	GPIO_PORTD_PCTL_R = 0x11000000;         // PD6 & PD7 as Tx & Rx of UART2
	GPIO_PORTD_AMSEL_R &= ~0xC0;            //disable analog for PD6 , PD7	
}

char UART_Receiver(void)  
{
	while((UART2_FR_R&0X10)!=0){};		//to check if receiver fifo is empty or full, if empty wait for the comming data
		 //it should be the data that we are going to process
		return (UART2_DR_R&0xFF);
}





// Function for Converting from degrees to radian
double Deg_Rad(double deg){
    return (deg * PI / 180);
}

// Measuring the distance by longitude and latitude
double Total_Distance(double long1, double long2, double lat1, double lat2) {
   double dlong = Deg_Rad(long2 - long1);
   double dlat = Deg_Rad(lat2 - lat1);
   double phi1 = Deg_Rad(lat1);
   double phi2 = Deg_Rad(lat2);
    // Haversine formula
   double a = pow(sin((0.5 * dlat)), 2) + cos(phi1) * cos(phi2) * pow(sin((0.5 * dlong)), 2);
   double d = 2 * R * asin(sqrt(a));
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
void LCD_showdist(int value){
    int i=0;
    int arr[10];
    int tmp=value;
    for(i=0 ; value!=0 ; i++){
        arr[i]=tmp % 10;
        value /=10;
        tmp=value;
    }
    for(  ; i!=0 ; i-- ){
        LCD_DATA(arr[i-1] + 48);
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

int main()
{
    CLK();
    PORTF_INIT();
    TARGET();
    LCD_init_PORT();
    LCD_COM(0x01);
    LCD_COM(0x80);
    D_MILLI(500);
    LCD_showword();
    D_MILLI(1);
    LCD_showdist(Dis);
    D_MILLI(500);
}

