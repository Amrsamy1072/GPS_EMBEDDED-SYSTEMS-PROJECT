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

char GTC()
{
    
    while ((UART5_FR_R & 0x10) != 0)
    {
    }
   
    return ( UART5_DR_R&0xFF);
}

bool GPS_stat()
{
  char t = GTC();
 
  
  if (t == '$')
  { array[0]=t;
    t = GTC();
   
    if (t == 'G')
    { array[1]=t;
      t = GTC();
    
      if (t == 'P')

      { array[2]=t;
        t = GTC();
   
        if (t == 'G')
        { array[3]=t;
          t = GTC();
    
          if (t == 'L')
          {array[4]=t;
            t = GTC();
       
             if (t == 'L')
             { array[5]=t;
              t = GTC();
      
              if (t == ',')
              {array[6]=t;
                t = GTC();
                if (t == ',')
                {
                  return false;
                }
                else
                {
                  return true;
                }
              }
            }
          }
        }
      }
    }
  }
   return false;
}
//3
  void  getdata()
  {
   
          int i=1;
          for(;i<40;i++)
          {
              array[i+6]=GTC();
              if(array[i+6]=='\n'||array[i+6]=='\r')
							
              break;
          }
                
  }

	long double GpsToDecimalDegrees(const char* nmeaPos)
{
  long double v= 0;
  if(strlen(nmeaPos)>5)
  {
    char integerPart[3+1];
    int digitCount= (nmeaPos[4]=='.' ? 2 : 3);
    memcpy(integerPart, nmeaPos, digitCount);
    integerPart[digitCount]= 0;
    nmeaPos+= digitCount;
    v= atoi(integerPart) + atof(nmeaPos)/60.;
	return v;
  }
}

	long double get_lat ()
{
	   
	     
        int i=7;
        int j=0;
	      char lat[11]={0};	
        for(;i<=16;i++)
       {
             lat[j]=array[i];
               j++;
       }
			 lat[10]='\n';
        return GpsToDecimalDegrees(lat);
}
		 
		 
long double get_lon ()
{
	
        int i=20;
         int j=0;
	      char lon[12]={0};
        for(i=20;i<=30;i++)
      {
            lon[j]=array[i];
             j++;
      }
			lon[11]='\n';
       return GpsToDecimalDegrees(lon);
      }


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
float Total_Distance(float long1,float long2,float latx1,float latx2)
{
    /* converting all coordinates to radian */
    float lat1 = Deg_Rad(latx1);
    float lon1 = Deg_Rad(long1);
    float lat2 = Deg_Rad(latx2);
    float lon2 = Deg_Rad(long2);

    if ((lat1 == lat2) && (lon1 == lon2)) {
        return Dis; /* if it's the same point, the distance between them is zero */
    }
    else {
        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
      double  dis = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2); /* Haversine's Formula */
        dis = 2 * asin(sqrt(dis));
        dis = dis * 6371000; /* distance in meters */
       Dis = Dis + dis;
        return Dis;
    }
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
                     GPIO_PORTF_DATA_R|=0X02;
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


