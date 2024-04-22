#define F_CPU 4000000UL
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

//volatile int pulseCount = 0;
volatile long signal_pulse;
volatile long signal_period;
int frequency;
uint16_t RPM;
float dutycycle;

void USART3_init(void);
void USART3_sendChar(char c);
void USART3_sendString(char *str);
void TCB0_init(void);
void EVSYS_init();

static int USART3_printChar(const char character, FILE *stream);


FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	USART3_init();
	EVSYS_init();
	TCB0_init();
	
	PORTB.DIR &= ~PIN5_bm;
	PORTB.PIN5CTRL |= PORT_PULLUPEN_bm;
	
	sei();

	while (1)
	{
		_delay_ms(1000);
		
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
		sei();
	}
}

// Interrupt Service Routine for capturing rising edges on tachometer pin
ISR(TCB0_INT_vect)
{
	cli();
	signal_pulse = TCB0.CCMP/4;
	signal_period = TCB0.CNT/4;
	frequency = F_CPU/signal_period;
	RPM =  (60.0/(2.0*0.00001*((float)signal_pulse/5)));
	dutycycle = 16.906006771355486 + 0.007366553738916978*RPM - 5.115980980300793 * pow(10, -7) * pow(RPM, 2) + 3.762891047688633 * pow(10, -11) * pow(RPM, 3) + 2.4564312000230716 * pow(10, -15) * pow(RPM, 4) - 1.2864319433167294 * pow(10, -19) * pow(RPM, 5) - 6.676372918605685 * pow(10, -24) * pow(RPM, 6);
	TCB0.INTFLAGS = TCB_CAPT_bm;		// Reset interrupt flag
	sei();
}

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
	EVSYS.CHANNEL0 = EVSYS_CHANNEL0_PORTB_PIN5_gc;				// 0x4A equals to PD2
	
	//Bind user TCB0CAPT to event system channel 2
	EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL0_gc;
}

//USART functions

void USART3_init(void){
	PORTB.DIR &= ~PIN1_bm;
	PORTB.DIR |= PIN0_bm;
	USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600);
	USART3.CTRLB |= USART_TXEN_bm;
	stdout = &USART_stream;
}

void USART3_sendChar(char c){
	while (!(USART3.STATUS & USART_DREIF_bm));
	USART3.TXDATAL = c;
}

void USART3_sendString(char *str){
	for(size_t i = 0; i < strlen(str); i++){
		USART3_sendChar(str[i]);
	}
}

static int USART3_printChar(char c, FILE *stream){
	USART3_sendChar(c);
	return 0;
}