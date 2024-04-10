
#define F_CPU 4000000UL
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

void USART3_init(void);
int USART3_printChar(const char character, FILE *stream);
FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	USART3_init();
	
	PORTC.DIRSET |= PIN5_bm;
	
	/* Timer/Counter */
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.EVCTRL	|= TCA_SINGLE_CNTAEI_bm |	TCA_SINGLE_EVACTA_CNT_POSEDGE_gc;
	
	/* Analog Comparator */
	AC0.CTRLA |= 0x1;
	AC0.CTRLB |= 0x00;
	AC0.MUXCTRL |= 0b00000011; // 0x3
	AC0.DACREF = (uint8_t) 250;
	
	/* VREF */
	VREF.ACREF |= 0x1;
	
	/* Event System */
	EVSYS.CHANNEL0 = 0x20; /* 0x20 tilsvarer EVSYS_CHANNEL0_AC0_OUT_gc*/
	EVSYS.USERTCA0CNTA = EVSYS_USER_CHANNEL0_gc;
	
	/* RTC */
	RTC.CTRLA |= RTC_RTCEN_bm | RTC_PRESCALER_DIV1024_gc;
	RTC.INTCTRL |= RTC_OVF_bm;
	RTC.CLKSEL |= RTC_CLKSEL_OSC1K_gc;
	RTC.PER |= 1;
	
	
	
	/* Replace with your application code */
	while (1)
	{
		_delay_ms(1000);
		PORTC.OUTTGL = PIN5_bm;
		//_delay_ms(1);
		
		//printf("hello\n");
		printf("%d\n", TCA0.SINGLE.CNT);
		TCA0.SINGLE.CNT = 0;
		
		
	}
}

void USART3_init(void)
{
	PORTB.DIRSET = PIN0_bm;
	PORTB.DIRCLR = PIN1_bm;
	USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600);
	USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
	stdout = &USART_stream;
}

int USART3_printChar(const char character, FILE *stream)
{
	while (!(USART3.STATUS & USART_DREIF_bm))	// Sjekker om forrige transmisjon er ferdig.
	{
		;
	}
	USART3.TXDATAL = (character); // Kan evt. bruke printf.
	
	return 0;
}

ISR(RTC_CNT_vect)	{
	if(RTC.INTFLAGS & RTC_OVF_bm)	{
		/* Kj�r kode */
		//secons ++;
		//TCA0.SINGLE.CNT	= 0;
	}
	
	RTC.INTFLAGS |= RTC_OVF_bm;
}
