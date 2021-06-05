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



//uart initilization
void uart(void){
	SYSCTL_RCGCUART_R |= 0x04; //activate UART2
	SYSCTL_RCGCGPIO_R |= 0x08; //activate PORTD
	UART2_CTL_R &= ~0x01; //disable the UART
	//BaudRate = 9600 --> 16MHZ /(16*9600) = 104.1667
	UART2_IBRD_R = 104; //integer part = 104
	UART2_FBRD_R = 11; //fractional part = 0.1667*64 = 11
	UART2_LCRH_R = 0x70; //8-bit data, no parity, one stop, FIFo.s enabled
	UART2_CTL_R |= 0x01;	//enable the UART
	UART2_CTL_R |= 0x200; to make uart receiver
	
	GPIO_PORTD_AFSEL_R |= 0xC0; //enable alternate function for PD6 & PD7
	GPIO_PORTD_DEN_R |= 0xC0; //configure PD6 & PD7 as digital I/O
	GPIO_PORTD_PCTL_R = 0x11000000; //configure PD6 & PD7 as Tx & Rx of UART1
	GPIO_PORTD_AMSEL_R &= ~0xC0; //disable analog on PD6 & PD7	
 	
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
void LCD_DATA(unsigned char data)
{
    GPIO_PORTA_DATA_R|=0x20;           // RS=1
    GPIO_PORTB_DATA_R=data;
    GPIO_PORTA_DATA_R|=0x80;           // EN = HIGH
    D_MICRO(0);
    GPIO_PORTA_DATA_R=0x00;            // EN = LOW
}
