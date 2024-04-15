/*
 * statemachine.c
 *
 * Created: 21.03.2024 11:18:08
 * Author : Meg
 */ 

#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "uart.h"
#include "switchstates1.h"
#include "eeprommem.h"
#include "PWM.h"


int main ( void )
{
	PORT_init();
	TCA0_init();
	USART3.CTRLA |= USART_RXCIE_bm ;
	USART3_init ();
	/* This delay invalidates the initial noise on the TX line , after device reset
	. */
	 sei();
	_delay_ms (10) ;
	
	FUSE.SYSCFG0 |=(0<<0);// eeprom is saved under chip erase
	eeprom_write_byte(start_fan_adress1,10);
	
	while (1)
	{
		if (data_ready_flag) {
			c = recived; // Update 'c' with the received character
			data_ready_flag = 0;
			// Process received_char as needed
			if(c != LF && c != CR){ // If received \r or \n
				command[index++] = c;
				if( index > MAX_COMMAND_LEN )
				{
					printf ("\r\n");
					index = 0;
				}
			}
			if(c == CR || c == '\n'){ // if recived \r
				command [index] = 0;
				index = 0;
		
		startMenu();	
			}
		}
	}
}

ISR (USART3_RXC_vect){
	recived = USART3_read();
	USART3.STATUS |= USART_RXCIF_bm;
	data_ready_flag = 1;
}

