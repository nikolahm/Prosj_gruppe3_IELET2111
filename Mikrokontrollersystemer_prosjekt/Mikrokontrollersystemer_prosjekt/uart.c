/*
 * uart.c
 *
 * Created: 11.04.2024 15:32:08
 *  Author: HS
 */ 
//this code is partially from LF 7 in mikrokontrollersystemer, it has been edited to adapt the project

// Init function
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
#include "eeprommem.h"
#include "RPM.h"



void USART3_init ( void )
{
	PORTB.DIRSET = PIN0_bm ; // Set TX pin to output
	PORTB.DIRCLR = PIN1_bm ; // Set RX pin to input
	USART3.BAUD = (uint16_t) USART3_BAUD_RATE(9600) ; // Set Baud rate 9600
	USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm ;
	stdout = & USART_stream ; // Replacing output stream
	
}
void USART3_sendChar ( char c){
	while (!( USART3.STATUS & USART_DREIF_bm )) // while data register not empty
	{
		;
	}
	USART3.TXDATAL = c;
	
	}
// Wrapping USART3_sendChar in a function computable with FDEV_SETUP_STREAM
int USART3_printChar ( char c, FILE * stream )
{
	USART3_sendChar (c);
	return 0;
}
// Function to send string
void USART3_sendString ( char * str )
{
	for ( size_t i = 0; i < strlen ( str ); i ++)
	{
		USART3_sendChar ( str [i]);
	}
}
// Function to read received char
uint8_t USART3_read ()
{
	while (!( USART3.STATUS & USART_RXCIF_bm ))
	{
		
		;
	}
	uint8_t src = USART3.RXDATAL ;
	USART3_sendChar ( src );
	return src ;
	
	}

uint8_t compareCommands(char* src, char* arrays[], uint8_t array_size) {//compares usart command to command array
	// Return index of command received or 255 if none
	for (uint8_t a = 0; a < array_size; a++) { //checks for lenght of array
		
		if (!strncmp(src, arrays[a], array_size)) { //if command is not equal to current char in array
			
			
			return a+1 ;
			
		}
	}
	return 255; //return command not in array
}
