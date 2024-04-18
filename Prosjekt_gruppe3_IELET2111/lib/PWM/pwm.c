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
void TCA1_init(void);
void PORT_init(void);
void speed_controll_0(uint8_t persentage);
void speed_controll_1(uint8_t persentage);
void speed_controll_2(uint8_t persentage);
void speed_controll_3(uint8_t persentage);
void speed_controll_4(uint8_t persentage);
void speed_controll_5(uint8_t persentage);
void speed_controll_6 (uint8_t persentage);
void speed_controll_7 (uint8_t persentage);


void speed_controll_0 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA0.SPLIT.LCMP0 = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA0.SPLIT.LCMP0 = (uint8_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA0.SPLIT.LCMP0 = (uint8_t)((PERIOD_VALUE * 1 / 100));
		}
	} 
	else
	{
		uint8_t speed_value = (uint8_t)((PERIOD_VALUE * persentage / 100));
		TCA0.SPLIT.LCMP0 = speed_value;
	}
}
void speed_controll_1 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA0.SPLIT.LCMP1 = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA0.SPLIT.LCMP1 = (uint8_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA0.SPLIT.LCMP1 = (uint8_t)((PERIOD_VALUE * 1 / 100));
		}
	}
	else
	{
		uint8_t speed_value = (uint8_t)((PERIOD_VALUE * persentage / 100));
		TCA0.SPLIT.LCMP1 = speed_value;
	}
}
void speed_controll_2 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA0.SPLIT.LCMP2 = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA0.SPLIT.LCMP2 = (uint8_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA0.SPLIT.LCMP2 = (uint8_t)((PERIOD_VALUE * 1 / 100));
		}
	}
	else
	{
		uint8_t speed_value = (uint8_t)((PERIOD_VALUE * persentage / 100));
		TCA0.SPLIT.LCMP2 = speed_value;
	}
}
void speed_controll_3 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA0.SPLIT.HCMP0 = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA0.SPLIT.HCMP0 = (uint8_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA0.SPLIT.HCMP0 = (uint8_t)((PERIOD_VALUE * 1 / 100));
		}
	}
	else
	{
		uint8_t speed_value = (uint8_t)((PERIOD_VALUE * persentage / 100));
		TCA0.SPLIT.HCMP0 = speed_value;
	}
}
void speed_controll_4 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA0.SPLIT.HCMP1 = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA0.SPLIT.HCMP1 = (uint8_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA0.SPLIT.HCMP1 = (uint8_t)((PERIOD_VALUE * 1 / 100));
		}
	}
	else
	{
		uint8_t speed_value = (uint8_t)((PERIOD_VALUE * persentage / 100));
		TCA0.SPLIT.HCMP1 = speed_value;
	}
}
void speed_controll_5 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA0.SPLIT.HCMP2 = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA0.SPLIT.HCMP2 = (uint8_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA0.SPLIT.HCMP2 = (uint8_t)((PERIOD_VALUE * 1 / 100));
		}
	}
	else
	{
		uint8_t speed_value = (uint8_t)((PERIOD_VALUE * persentage / 100));
		TCA0.SPLIT.HCMP2 = speed_value;
	}
}
void speed_controll_6 (uint8_t persentage)
{
		if (persentage > 100)
		{
			TCA1.SINGLE.CMP0BUF = PERIOD_VALUE;
		} else if (persentage < 20)
		{
			TCA1.SINGLE.CMP0BUF = (uint8_t)((PERIOD_VALUE * 20 / 100));
			if (persentage == 0){
				TCA1.SINGLE.CMP0BUF = (uint8_t)((PERIOD_VALUE * 1 / 100));
			}
		}
		else
		{
			uint8_t speed_value = (uint8_t)((PERIOD_VALUE * persentage / 100));
			TCA1.SINGLE.CMP0BUF = speed_value;
		}
}
void speed_controll_7 (uint8_t persentage)
{
	if (persentage > 100)
	{
		TCA1.SINGLE.CMP1BUF = PERIOD_VALUE;
	} else if (persentage < 20)
	{
		TCA1.SINGLE.CMP1BUF = (uint8_t)((PERIOD_VALUE * 20 / 100));
		if (persentage == 0){
			TCA1.SINGLE.CMP1BUF = (uint8_t)((PERIOD_VALUE * 1 / 100));
		}
	}
	else
	{
		uint8_t speed_value = (uint8_t)((PERIOD_VALUE * persentage / 100));
		TCA1.SINGLE.CMP1BUF = speed_value;
	}
}
void TCA0_init(void)
{
	
	/* set waveform output on PORT D*/
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
	TCA0.SPLIT.CTRLD = 1 << 0;
	TCA0.SPLIT.CTRLB = 0xff; /* enable compare
	channel 0 *	mode */
	
	/* set PWM frequency and duty cycle (50%) */
	TCA0.SPLIT.LPER = PERIOD_VALUE;
	TCA0.SPLIT.HPER = PERIOD_VALUE;
	

	TCA0.SPLIT.CTRLA |= TCA_SPLIT_CLKSEL_DIV2_gc /* set clock source
	(sys_clk/4) */
	| TCA_SPLIT_ENABLE_bm; /* start timer */
}
void TCA1_init(void)
{
	/* set waveform output on PORT D*/
	PORTMUX.TCAROUTEA = PORTMUX_TCA1_PORTB_gc;

	TCA1.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm |TCA_SINGLE_CMP2EN_bm /* enable compare
	channel 0 */
	| TCA_SINGLE_WGMODE_SINGLESLOPE_gc; /* set dual-slope PWM
	mode */

	/* disable event counting */
	TCA1.SINGLE.EVCTRL &= 0;

	/* set PWM frequency and duty cycle (50%) */
	TCA1.SINGLE.PER = PERIOD_VALUE;
	

	TCA1.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV2_gc /* set clock source
	(sys_clk/4) */
	| TCA_SINGLE_ENABLE_bm; /* start timer */
	
}
void PORT_init(void)
{
	/* set pin 0 of PORT D as output */
	PORTD.DIRSET |= PIN0_bm;
	PORTD.DIRSET |= PIN1_bm;
	PORTD.DIRSET |= PIN2_bm;
	PORTD.DIRSET |= PIN3_bm;
	PORTD.DIRSET |= PIN4_bm;
	PORTD.DIRSET |= PIN5_bm;
	
	PORTB.DIRSET |= PIN0_bm;
	PORTB.DIRSET |= PIN1_bm;
}


