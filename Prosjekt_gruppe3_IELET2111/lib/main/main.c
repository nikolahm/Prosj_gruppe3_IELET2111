/*
 * statemachine.c
 *
 * Created: 21.03.2024 11:18:08
 * Author : Meg
 */ 

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
#include "switchstates1.h"
#include "eeprommem.h"
#include "PWM.h"
#include "RPM.h"





int main ( void )
{
	PORT_init(); //initialize pwm
	TCA0_init(); //initialize the TCA0
	USART3.CTRLA |= USART_RXCIE_bm ; //
	USART3_init ();
	/* This delay invalidates the initial noise on the TX line , after device reset
	. */
	
	
	 sei();  //activate global interupts
	 initialize_adresses();
	_delay_ms (10) ;
	initialize_rpm();
	_delay_ms (10) ;
	twi_master_init_aht10();
	_delay_ms (1000);
	
	 //adress_space_clear(); if adresses are to be cleared manualy
	
	// FUSE.SYSCFG0 |=(0<<1); // eeprom is saved under chip erase, optional
	
	while (1)
	{ 
		RPM_value();
		automaticspeed();
		average_rpm(RPM,&current_fan_adress1,&store_rpm1,&n_count_adress1,&start_fan_adress1);

		if (1==1/*data_ready_flag*/) { //if interupt on usart has happend, change to data ready flag if interupt is used
			recived = USART3_read();
			c = recived; // Update 'c' with the received character
			data_ready_flag = 0; //disable so it only runs once each message and iteration
			// Process received_char as needed
			if(c != LF && c != CR){ // If received \r or \n
				command[index++] = c; 
				if( index > MAX_COMMAND_LEN ) // if command to large,print newline
				{
			
					
					index = 0;
					printf("\r");
				}
			}
			if(c == CR || c == LF){ // if recived \r or \n
				command [index] = 0; 
				index = 0;
		startMenu();	//main function for the uartmenu
		
		
			}
		}
		
	}
	
	
}

/*ISR (USART3_RXC_vect){
	recived = USART3_read(); //variable containing information about the message
	USART3.STATUS |= USART_RXCIF_bm; //usart status set to clear, so information can be recived next interupt
	data_ready_flag = 1; //set flag to recived information on usart
}*/

ISR(TCB0_INT_vect)
{
	signal_pulse = TCB0.CCMP/4;
	signal_period = TCB0.CNT/4;
			// Reset interrupt flag
	TCB0.INTFLAGS = TCB_CAPT_bm;
}
