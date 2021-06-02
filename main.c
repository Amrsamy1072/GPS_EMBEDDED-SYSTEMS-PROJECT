#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "math.h"
#include "stdint.h"

#define UNLOCK_PORT 0x4C4F434B

void SystemInit(){}
void PORTF_init (){
	 // ENABLE CLOCK FOR PORT F
   SYSCTL_RCGCGPIO_R |=  0x20;                
	 while((SYSCTL_PRGPIO_R & 0x20) == 0){};    // Wait until clock is stable 
		 
	 // PORT F INITIALIZATION for RED LED
	 GPIO_PORTF_LOCK_R = UNLOCK_PORT;           // Unlock PORTF 
	 GPIO_PORTF_CR_R |= 0x02;                   // Allow changes to PF1 (RED COLOR)
	 GPIO_PORTF_AMSEL_R &= ~0x02;               // Disable analog for PF1 
	 GPIO_PORTF_AFSEL_R &= ~0x02;               // Disable alternate function for PF1
	 GPIO_PORTF_PCTL_R &= ~0X000000F0;          // Select GPIO functionality
	 GPIO_PORTF_DIR_R |= 0x02;                  // Set direction of PF1 as output
	 GPIO_PORTF_DEN_R |= 0x02;                  // Enable digital in PF1
	 }
