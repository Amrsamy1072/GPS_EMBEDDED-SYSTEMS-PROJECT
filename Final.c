
//1

//2

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






