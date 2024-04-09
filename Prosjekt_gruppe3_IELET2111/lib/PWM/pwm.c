/*
 * prosjektPWMstyring.c
 *
 * Created: 3/20/2024 10:22:28 AM
 * Author : nicol
 */ 


#define PERIOD_VALUE (0x50)
#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
/*Using default clock 3.33MHz */
void TCA0_init(void);
void PORT_init(void);
void speed_controll_1(uint8_t persentage);
void speed_controll_2(uint8_t persentage);
void speed_controll_3(uint8_t persentage);


int main(void)
{
	PORT_init();
	TCA0_init();
	while (1)
	{
		speed_controll_1(0);
		speed_controll_2(50);
		speed_controll_3(0);
	}
}

void speed_controll_1 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA0.SINGLE.CMP0BUF = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA0.SINGLE.CMP0BUF = (uint16_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA0.SINGLE.CMP0BUF = (uint16_t)((PERIOD_VALUE * 1 / 100));
		}
	} 
	else
	{
		uint16_t speed_value = (uint16_t)((PERIOD_VALUE * persentage / 100));
		TCA0.SINGLE.CMP0BUF = speed_value;
	}
}
void speed_controll_2 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA0.SINGLE.CMP1BUF = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA0.SINGLE.CMP1BUF = (uint16_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA0.SINGLE.CMP1BUF = (uint16_t)((PERIOD_VALUE * 1 / 100));
		}
	}
	else
	{
		uint16_t speed_value = (uint16_t)((PERIOD_VALUE * persentage / 100));
		TCA0.SINGLE.CMP1BUF = speed_value;
	}
}
void speed_controll_3 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA0.SINGLE.CMP2BUF = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA0.SINGLE.CMP2BUF = (uint16_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA0.SINGLE.CMP2BUF = (uint16_t)((PERIOD_VALUE * 1 / 100));
		}
	}
	else
	{
		uint16_t speed_value = (uint16_t)((PERIOD_VALUE * persentage / 100));
		TCA0.SINGLE.CMP2BUF = speed_value;
	}
}

void TCA0_init(void)
{
	/* set waveform output on PORT D*/
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc | PORTMUX_TCA0_PORTE_gc;

	TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm |TCA_SINGLE_CMP2EN_bm /* enable compare
	channel 0 */
	| TCA_SINGLE_WGMODE_SINGLESLOPE_gc; /* set dual-slope PWM
	mode */

	/* disable event counting */
	TCA0.SINGLE.EVCTRL &= 0;

	/* set PWM frequency and duty cycle (50%) */
	TCA0.SINGLE.PER = PERIOD_VALUE;
	

	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV2_gc /* set clock source
	(sys_clk/4) */
	| TCA_SINGLE_ENABLE_bm; /* start timer */
}
void PORT_init(void)
{
	/* set pin 0 of PORT D as output */
	PORTD.DIRSET |= PIN0_bm;
	PORTD.DIRSET |= PIN1_bm;
	PORTD.DIRSET |= PIN2_bm;
}


