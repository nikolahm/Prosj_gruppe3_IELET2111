#define F_CPU 4000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "uart.h"
#include "switchstates.h"
#include "eeprommem.h"
#include "PWM.h"
#include "RPM.h"
#include "twi_aht10.h"

//Variables from fan reading:
volatile uint16_t signal_pulse = 0;
volatile uint16_t signal_period = 0;
volatile uint16_t rpm_from_inter;

int main ( void )
{
	PORT_init(); 																		//initialize pwm
	TCA0_init(); 																		//initialize the TCA0
	USART3.CTRLA |= USART_RXCIE_bm ; 													// set usart read register
	USART3_init (); 																	//initialize usart3 
	 EVSYS_init(); 																		//initialize event system
	 TCB0_init(); 																		// initialize the TCB0
	 		
	 PORTB.DIR &= ~PIN5_bm;
	 PORTB.PIN5CTRL |= PORT_PULLUPEN_bm;
	 
	_delay_ms (10) ;
	initialize_rpm(); 																	//initialize rpm reading
	sei();  																			//activate global interupts
	_delay_ms (10) ;
	twi_master_init_aht10(); 															//initialize setup for TWI to AHT10 sensor
	_delay_ms (1000);
	initialize_adresses(); 																//updates last adresses used
	automaticspeed_limiter=0; 															//limit times the rpm and eeprom is written to
	 //adress_space_clear(); 															//If adresses are to be cleared manualy
	
	// FUSE.SYSCFG0 |=(0<<1); 															//Eeprom is saved under chip erase, optional
	
	while (1)
	{
		//	_delay_ms(100);
		cli();
		automaticspeed_limiter++;
		if(automaticspeed_limiter>10){ 													//10 iteration before 1 run
		automaticspeed();																//needs to be updated always
		sei();																			//activate interupt for short time
		cli(); 																			//deactivate interupt
		automaticspeed_limiter=0;
		average_rpm(RPM,&current_fan_adress1,&store_rpm1,&n_count_adress1,start_fan_adress1); //eeprom update for pred-values
		}
		
		if (data_ready_flag) { 															//if interupt on usart has happend, change to data ready flag if interupt is used
 			
			//recived = USART3_read();
			c = recived; 																// Update 'c' with the received character
			data_ready_flag = 0; 														//Disable so it only runs once each message and iteration
			
			// Process received_char as needed
			if(c != LF && c != CR){ 													// If received \r or \n
				command[index++] = c; 
				if( index > MAX_COMMAND_LEN ) 											//If command to large; print newline
				{
					index = 0;
					printf("\r");
				}
			}
			if(c == CR || c == LF){ 													//If recived \r or \n
				command [index] = 0; 
				index = 0;
		startMenu();																	//Main function for the USART menu
		
		
			}
		}
		sei();																			//Activate interupts
	}
	
	
}


//Interupt for reading from the fans
ISR(TCB0_INT_vect) 
{
	cli();																				//Disable interrupts globally while data is collected
	signal_pulse = TCB0.CCMP/4;															//Calculate high pulse length
	signal_period = TCB0.CNT/4;															//Collect period length, this can be used for calculating frequency, if needed.
	RPM = (60.0/(pow(10, -6)*signal_pulse*4));											//Calculate RPM

	TCB0.INTFLAGS = TCB_CAPT_bm;														//Reset interrupt flag
	sei();																				//Resume interrupts globally
	
}


//Interrupt for receiving information from USART
ISR (USART3_RXC_vect){ 
	recived = USART3_read();  															//variable containing information about the message
	USART3.STATUS |= USART_RXCIF_bm; 													//usart status set to clear, so information can be recived next interupt
	data_ready_flag = 1;																//set flag to recived information on usart
}
