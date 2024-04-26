
/*
 * RPM.c
 *
 * Created: 21.04.2024 15:27:41
 *  Author: Meg
 */ 
#define F_CPU 4000000UL
//#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "RPM.h"
//volatile int pulseCount = 0;

int frequency;
//uint16_t RPM;
float dutycycle;

void TCB0_init(void);
void EVSYS_init();

void initialize_rpm(){
		EVSYS_init();
		TCB0_init();
		
		PORTB.DIR &= ~PIN5_bm;
		PORTB.PIN5CTRL |= PORT_PULLUPEN_bm;
		}
/*int RPMstuff(void)
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

			char freqStr[10];
			sprintf(freqStr, "%d\r\n", frequency/4);
			USART3_sendString("\nFrequency [Hz]: ");
			USART3_sendString(freqStr);
			
			char rpmStr[10];
			sprintf(rpmStr, "%d\r\n", RPM);
			USART3_sendString("\nRPM [s]: ");
			USART3_sendString(rpmStr);
			
			char dutyStr[15];
			sprintf(dutyStr, "%d\r\n", (int)dutycycle);
			USART3_sendString("\nDuty Cycle [%]: ");
			USART3_sendString(dutyStr);
		
	}
}*/

// Interrupt Service Routine for capturing rising edges on tachometer pin


void TCB0_init(void){
	//Config register CTRLB
	TCB0.CTRLB  =//0<< TCB_ASYNC_bp       /* Asynchronous Enable: disabled */
	TCB_CCMPEN_bm		/* Pin Output Enable: disabled */
	//|0<< TCB_CCMPINIT_bp	/* Pin Initial State: disabled */
	| TCB_CNTMODE_FRQPW_gc;	/* Input Capture pulsewidth measurement */
	
	//TCB0.INTCTRL = 0b00000001;

	//Config event control
	TCB0.EVCTRL = TCB_CAPTEI_bm		/* Event Input Enable: enabled */
	| TCB_EDGE_bm;		/* Event Edge: enabled */
	//| TCB_FILTER_bm;	/* Input Capture Noise Cancellation Filter: disabled */

	//Config interrupt control
	TCB0.INTCTRL= TCB_CAPT_bm;		/* Capture or Timeout: enabled */
	//| TCB_OVF_bm;		/* OverFlow Interrupt: disabled */

	//Config register CTRLA
	TCB0.CTRLA = TCB_CLKSEL_DIV1_gc     /* CLK_PER/2 */
	| TCB_ENABLE_bm		/* Enable: enabled */
	| TCB_RUNSTDBY_bm;	/* Run Standby: disabled */
	//|0<< TCB_SYNCUPD_bp		/* Synchronize Update: disabled */
	//|0<< TCB_CASCADE_bp;	/* Cascade Two Timer/Counters: disabled */
	
	//TCB0.CCMP = 80;
}

void EVSYS_init(void){
	
	//Set pin PD2 to channel 2 in the event system
	EVSYS.CHANNEL0 = EVSYS_CHANNEL0_PORTB_PIN5_gc;
	
	//Bind user TCB0CAPT to event system channel 2
	EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL0_gc;
}

int RPM_value(uint16_t var){
	
	uint16_t RPM =  var;
	
	
	return  RPM;
	
}
