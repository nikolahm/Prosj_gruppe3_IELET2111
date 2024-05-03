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
#include "switchstates.h"
#include "eeprommem.h"
#include "PWM.h"
#include "RPM.h"
#include "twi_aht10.h"
//variables from fan reading
volatile uint16_t signal_pulse = 0;
volatile uint16_t signal_period = 0;
volatile uint16_t rpm_from_inter;

int main ( void )
{
	PORT_init(); //initialize pwm
	TCA0_init(); //initialize the TCA0
	USART3.CTRLA |= USART_RXCIE_bm ; // set usart read register
	USART3_init (); //initialize usart3 
	 EVSYS_init(); //initialize event system
	 TCB0_init(); // initialize the TCB0
	 		
	 PORTB.DIR &= ~PIN5_bm;
	 PORTB.PIN5CTRL |= PORT_PULLUPEN_bm;
	 
	_delay_ms (10) ;
	initialize_rpm(); //initialize rpm reading
	sei();  //activate global interupts
	_delay_ms (10) ;
	twi_master_init_aht10(); //initialize setup for TWI to AHT10 sensor
	_delay_ms (1000);
	initialize_adresses(); //updates last adresses used
	automaticspeed_limiter=0; //limit times the rpm and eeprom is written to
	 //adress_space_clear(); if adresses are to be cleared manualy
	
	// FUSE.SYSCFG0 |=(0<<1); // eeprom is saved under chip erase, optional
	
	while (1)
	{
		//	_delay_ms(100);
		cli();
		automaticspeed_limiter++;
		if(automaticspeed_limiter>10){ //10 iteration before 1 run
		automaticspeed();//needs to be updated always
		sei();//activate interupt for short time
		cli(); //deactivate interupt
		automaticspeed_limiter=0;
		average_rpm(RPM,&current_fan_adress1,&store_rpm1,&n_count_adress1,start_fan_adress1); //eeprom update for pred-values
		}
		
		if (data_ready_flag) { //if interupt on usart has happend, change to data ready flag if interupt is used
 			//recived = USART3_read();
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
		sei();//activate interupts
	}
	
	
}



ISR(TCB0_INT_vect) //interupt for reading from the fans
{
	cli();
	signal_pulse = TCB0.CCMP/4;
	signal_period = TCB0.CNT/4;
	RPM = (60.0/(2.0*0.00001*((float)signal_pulse/5)));
			// Reset interrupt flag
	TCB0.INTFLAGS = TCB_CAPT_bm;
//	printf("%d\n",rpm_from_inter);
	sei();
	
}


ISR (USART3_RXC_vect){ //interupt for reciving information from usart
	recived = USART3_read();  //variable containing information about the message
	USART3.STATUS |= USART_RXCIF_bm; //usart status set to clear, so information can be recived next interupt
	data_ready_flag = 1; //set flag to recived information on usart
}
