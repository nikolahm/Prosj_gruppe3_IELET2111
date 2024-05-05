#define F_CPU 4000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "RPM.h"

int frequency;
float dutycycle;

void TCB0_init(void);
void EVSYS_init();

//Function to setup everything needed for RPM calculations to work
void initialize_rpm(){
		EVSYS_init();
		TCB0_init();
		
		PORTB.DIR &= ~PIN5_bm;															//Set PB5 to input
		PORTB.PIN5CTRL |= PORT_PULLUPEN_bm;												//Enable pullup on PB5
		}

/*int RPMstuff(void)																	//Function for printing TCB values for debugging
{
		if (!(TCB0.INTFLAGS))
		{
			
			char pulseStr[10];
			sprintf(pulseStr, "%ld\r\n", signal_pulse);
			USART3_sendString("\n\nSignal pulse [us]: ");
			USART3_sendString(pulseStr);
			
			char periodStr[10];
			sprintf(periodStr, "%ld\r\n", signal_period);
			USART3_sendString("\nSignal period [us]: ");
			USART3_sendString(periodStr);
			
			char rpmStr[10];
			sprintf(rpmStr, "%d\r\n", RPM);
			USART3_sendString("\nRPM [s]: ");
			USART3_sendString(rpmStr);
		
	}
}*/

// Interrupt Service Routine for capturing rising edges on tachometer pin


void TCB0_init(void){
	//Config register CTRLB
	TCB0.CTRLB  =
	TCB_CCMPEN_bm																		/* Pin Output Enable: enabled */
	| TCB_CNTMODE_FRQPW_gc;																/* Input Capture pulsewidth measurement mode*/
	//| TCB_ASYNC_bm       																/* Asynchronous Enable: disabled */
	//| TCB_CCMPINIT_bm																	/* Pin Initial State: disabled */

	//Config event control
	TCB0.EVCTRL = 
	TCB_CAPTEI_bm																		/* Event Input Enable: enabled */
	| TCB_EDGE_bm;																		/* Event Edge: enabled */
	//| TCB_FILTER_bm;																	/* Input Capture Noise Cancellation Filter: disabled */

	//Config interrupt control
	TCB0.INTCTRL= 
	TCB_CAPT_bm;																		/* Capture or Timeout: enabled */
	//| TCB_OVF_bm;																		/* OverFlow Interrupt: disabled */

	//Config register CTRLA
	TCB0.CTRLA = 
	TCB_CLKSEL_DIV1_gc     																/* CLK_PER/1 AKA no prescaler */
	| TCB_ENABLE_bm																		/* Enable TCB: enabled */
	| TCB_RUNSTDBY_bm;																	/* Run Standby: enabled */
	//| TCB_SYNCUPD_bm																	/* Synchronize Update: disabled */
	//| TCB_CASCADE_bm;																	/* Cascade Two Timer/Counters: disabled */
}

//Event system configuration function
void EVSYS_init(void){

	EVSYS.CHANNEL0 = EVSYS_CHANNEL0_PORTB_PIN5_gc;										//Set pin PB5 to channel 0 in the event system
	
	EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL0_gc;										//Bind user TCB0CAPT to event system channel 0
}

int RPM_value(uint16_t var){
	
	uint16_t RPM =  var;																//Sets the RPM variable equal to var
	
	return  RPM;
}
