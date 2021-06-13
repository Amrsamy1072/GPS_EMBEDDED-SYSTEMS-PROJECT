





















































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











