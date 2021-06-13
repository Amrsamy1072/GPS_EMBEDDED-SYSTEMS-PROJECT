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


























