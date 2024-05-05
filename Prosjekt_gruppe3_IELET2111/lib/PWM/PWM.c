#define PERIOD_VALUE (0x4F) 	// Define period value for PWM 
#define F_CPU 4000000 		// Define CPU frequency 

/* Include necessary AVR header files */
#include <avr/io.h>
#include <util/delay.h>

/* Defining all the functions used in the program */
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

/**
 * @brief Control PWM duty cycle for channel 0.
 * 
 * @param persentage Percentage of duty cycle (0-100).
 * @return void
 */
void speed_controll_0 (uint8_t persentage)
{
	 /* Check if percentage is greater than 100% */
	if (persentage > 100)
	{
		/* Set maximum duty cycle */
		TCA0.SPLIT.LCMP0 = PERIOD_VALUE;
	} else if (persentage < 20) // Check if percentage is less than 20%
	{
		/* Set duty cycle to 20%, fan can't spin for  */
		TCA0.SPLIT.LCMP0 = (uint8_t)((PERIOD_VALUE * 20 / 100));
		/* Stopp fan compleatly if persentage = 0*/
		if (persentage == 0){
			TCA0.SPLIT.LCMP0 = (uint8_t)((PERIOD_VALUE * 1 / 100));
		}
	} 
	else
	{
		/* Calculate duty cycle based on percentage */
		uint8_t speed_value = (uint8_t)((PERIOD_VALUE * persentage / 100));
	     	/* Set duty cycle */
		TCA0.SPLIT.LCMP0 = speed_value;
	}
}

/* Functions speed_controll_1 to speed_controll_7 follow the same pattern as speed_controll_0 */

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

/**
 * @brief Initialize Timer/Counter module TCA0 for PWM.
 */
void TCA0_init(void)
{
	
	/* set waveform output on PORT D*/
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
	/* Enable split mode */
	TCA0.SPLIT.CTRLD = 1 << 0;
	/* Enable all compare channel modes */
	TCA0.SPLIT.CTRLB = 0xff;
	
	/* Set PWM frequency and duty cycle */
	TCA0.SPLIT.LPER = PERIOD_VALUE;
	TCA0.SPLIT.HPER = PERIOD_VALUE;
	

	TCA0.SPLIT.CTRLA |= TCA_SPLIT_CLKSEL_DIV2_gc /* set clock source (sys_clk/2) */
	| TCA_SPLIT_ENABLE_bm; /* start timer */
}
/**
 * @brief Initialize Timer/Counter module TCA1 for PWM.
 */
void TCA1_init(void)
{
	/* Set waveform output on PORT C */	
	PORTMUX.TCAROUTEA = PORTMUX_TCA1_PORTC_gc;

	/* enable compare channel 0, 1, and 2 */
	TCA1.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm |TCA_SINGLE_CMP2EN_bm 
	| TCA_SINGLE_WGMODE_SINGLESLOPE_gc; /* set single-slope PWM mode */

	/* disable event counting */
	TCA1.SINGLE.EVCTRL &= 0;

	 /* Set PWM frequency and duty cycle */
	TCA1.SINGLE.PER = PERIOD_VALUE;
	
	/* Set clock source and start timer */
	TCA1.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV2_gc | TCA_SINGLE_ENABLE_bm;
	
}
/**
 * @brief Initialize PORT D and PORT G for PWM output.
 */
void PORT_init(void)
{
    	/* Set pin 0 to 5 of PORT D as output */
	PORTD.DIRSET |= PIN0_bm;
	PORTD.DIRSET |= PIN1_bm;
	PORTD.DIRSET |= PIN2_bm;
	PORTD.DIRSET |= PIN3_bm;
	PORTD.DIRSET |= PIN4_bm;
	PORTD.DIRSET |= PIN5_bm;

  	/* Set pin 0 and 1 of PORT C as output */
	PORTC.DIRSET |= PIN0_bm;
	PORTC.DIRSET |= PIN1_bm;
}
