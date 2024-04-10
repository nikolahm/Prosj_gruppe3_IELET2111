#define F_CPU 4000000UL
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile uint32_t pulseCount = 0;
//volatile uint32_t timeElapsed = 0;

void USART3_init(void);
int USART3_printChar(const char character, FILE *stream);
FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	USART3_init();
	

	// Configure tachometer pin (PD2) as input with pull-up enabled
	PORTD.IN |= PIN2_bm;
	PORTD.PIN2CTRL |= PORT_PULLUPEN_bm;

	// Set pin PC5 as output for LED indication
	PORTC.DIRSET |= PIN5_bm;

	// Enable Timer/Counter TCB0 interrupt
	TCB0.INTCTRL |= TCB_CAPT_bm;
	
	// Configure TCB0 for capturing rising edges on tachometer pin (PD2)
	TCB0.CTRLB |= TCB_CNTMODE_PW_gc;
	TCB0.EVCTRL = TCB_CAPTEI_bm | TCB_EDGE_bm;
	//TCB0.CCMP = 0xFFFF; // Set maximum compare value

	// Enable interrupts
	sei();

	/* Event System */
	EVSYS.CHANNEL2 = 0x4A; // 0x4A equals to PD2
	EVSYS.USERTCB0CAPT = EVSYS_CHANNEL02_bm;
	
	// Enable Timer/Counter TCB0
	TCB0.CTRLA = TCB_CLKSEL_DIV1_gc | TCB_ENABLE_bm;	// Configure TCB0 to use peripheral clock with no prescaler

	while (1)
	{
		_delay_ms(1000);
		// Calculate RPM and send over USART
		uint32_t rpm = 0;
		if (TCB0.CNT > 0)
		{
			rpm = (uint32_t)(pulseCount); // Calculate RPM from pulse count and time elapsed			(40000000UL * pulseCount) / (TCB0.CCMP * 2 * 7)
		}
		printf("RPM: %lu\n", rpm);

		// Reset pulse count for next calculation
		//pulseCount = 0;
	}
}

// Interrupt Service Routine for capturing rising edges on tachometer pin
ISR(TCB0_INT_vect)
{
	pulseCount++; // Increment pulse count
	printf("Interrupt Triggered");
	TCB0.INTFLAGS = 1; // Clear interrupt flag
	//TCA0.SINGLE.CNT = 0;
}

void USART3_init(void)
{
	PORTB.DIRSET = PIN0_bm; // TXD3 as output
	PORTB.DIRCLR = PIN1_bm; // RXD3 as input
	USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600); // Set baud rate
	USART3.CTRLB |= USART_TXEN_bm; // Enable transmitter
	stdout = &USART_stream; // Redirect standard output to USART3
}

int USART3_printChar(const char character, FILE *stream)
{
	while (!(USART3.STATUS & USART_DREIF_bm)) // Wait for data register to be empty
	{
		;
	}
	USART3.TXDATAL = character; // Send character
	return 0;
}