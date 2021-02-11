#include <stdio.h>
#include <stdint.h>
#include "MK64F12.h"

#define FALSE 0
#define TRUE 0x10

void delay(uint32_t delay);

int main(void) {
	/**Activating the GPIOB and GPIOE clock gating*/
	SIM->SCGC5 = 0x2E00;
	/**Pin control configuration of GPIOB pin22 and pin21 as GPIO*/
	PORTB->PCR[21] = 0x00000100;
	PORTB->PCR[22] = 0x00000100;
	/**Pin control configuration of GPIOC pin6 as GPIO with is pull-up resistor enabled*/
	PORTC->PCR[6] = 0x00000103;
	/**Pin control configuration of GPIOE pin26 as GPIO*/
	PORTA->PCR[4]=	0x00000103;
	PORTE->PCR[26] = 0x00000100;
	/**Assigns a safe value to the output pin21 of the GPIOB*/
	GPIOB->PDOR = 0x00200000;
	/**Assigns a safe value to the output pin22 of the GPIOB*/
	GPIOB->PDOR |= 0x00400000;
	/**Assigns a safe value to the output pin26 of the GPIOE*/
	GPIOE->PDOR |= 0x04000000;

	GPIOC->PDDR &=~(0x40);
	/**Configures GPIOB pin21 as output*/
	GPIOA->PDDR &=~(0x10); //salida
	GPIOB->PDDR = 0x00200000;
	/**Configures GPIOB pin22 as output*/
	GPIOB->PDDR |= 0x00400000;
	/**Configures GPIOE pin26 as output*/
	GPIOE->PDDR |= 0x04000000;
	uint32_t input_value=0;
	uint32_t time=0;
	uint32_t i=0;

    while(1) {
    	/**Reads all the GPIOA*/
		input_value = GPIOA->PDIR;
		/**Masks the GPIOA in the bit of interest*/
		input_value = input_value & 0x10;

		time = GPIOC->PDIR;
		if(0x40==time)
		{
			time=300000;
		}
		else
		{
			time=100000;
		}
		if(TRUE == input_value)
		{
			for(i=0; i<2;i++)
			{
	    	GPIOB->PCOR |= 0x00400000;/**Blue led off*/
			delay(time);
			GPIOB->PSOR |= 0x00400000;/**Read led off*/

	    	GPIOE->PCOR |= 0x04000000;/**Blue led off*/
			delay(time);
			GPIOE->PSOR |= 0x04000000;/**Read led off*/

			GPIOB->PCOR |= 0x00200000;/**Green led off*/
			delay(time);
			GPIOB->PSOR |= 0x00200000;/**Green led off*/
			}

		}
		else{
	    	for(i=0; i<6;i++){
				GPIOB->PTOR |= 0x00600000;
				GPIOE->PTOR |= 0x04000000;
				delay(time);
	    	}

		}
    }
    return 0 ;
}


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
void delay(uint32_t delay)
{
	volatile uint32_t counter;

	for(counter=delay; counter > 0; counter--)
	{
		__asm("nop");
	}
}
