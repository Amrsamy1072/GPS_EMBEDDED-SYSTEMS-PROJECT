#














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
