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


























int main()
{
	long double lon2=0;
  long double lat2=0;
	long double lat1=0;
	long double lon1=0;
	char charray[8]={0};
	bool x=false;
	
    CLK();
    PORTF_INIT();
    TARGET();
    LCD_init_PORT();
    UART5_Init();
	while(1)
		{
    x=GPS_stat();
	 
	 if (x==true){
		  getdata();
		  lat1=get_lat ();
		  lon1=get_lon ();

	
 while(1){
	x=GPS_stat();
	  if (x==true){
	 getdata();
		  lon2=get_lon ();
		  lat2=get_lat ();
		 Dis = Total_Distance (lon1,  lon2,  lat1,  lat2);
			     sprintf(charray, "%2.2f", Dis);
			 lat1=lat2;
			 lon1=lon2;
	  LCD_COM(0x01);
    LCD_COM(0x80);
    D_MILLI(500);
    LCD_showword();
    D_MILLI(1);
		LCD_printS(charray);
    D_MILLI(500);
			if (Dis > 100) {
GPIO_PORTF_DATA_R|=0X06;
			}

			
		
		 }
			else
				continue;
     }
	

     }
	 else
		 continue;
	 }
}
