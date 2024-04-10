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
#include "statemachine.h"

#define F_CPU 4000000UL


static char *choicearray[5]={

	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
};





// Init function
void USART3_init ( void )
{
	PORTB.DIRSET = PIN0_bm ; // Set TX pin to output
	PORTB.DIRCLR = PIN1_bm ; // Set RX pin to input
	USART3.BAUD = (uint16_t) USART3_BAUD_RATE(9600) ; // Set Baud rate 9600
	USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm ;
	stdout = & USART_stream ; // Replacing output stream
	
}// Function to send char
void USART3_sendChar ( char c)
{
	while (!( USART3.STATUS & USART_DREIF_bm )) // while data register not empty
	{
		;
	}
	USART3.TXDATAL = c;
}
// Wrapping USART3_sendChar in a function computable with FDEV_SETUP_STREAM
static int USART3_printChar ( char c, FILE * stream )
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

uint8_t compareCommands(char* src, char* arrays[], uint8_t array_size) {
	// Return index of command received or 255 if none
	for (uint8_t i = 0; i < array_size; i++) {
		
		if (!strncmp(src, arrays[i], array_size)) {
			
			
			return i+1 ;
			
		}
	}
	return 255;
}
int main ( void )
{
	USART3.CTRLA |= USART_RXCIE_bm ;
	USART3_init ();
	/* This delay invalidates the initial noise on the TX line , after device reset
	. */
	 sei();
	_delay_ms (10) ;
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

void startMenu(){
	switch (start_var)
	{
		case 1:
		
		modesMenu();
		
		break;
		
		case 2:
		printf("you have chosen the second menu");
		break;
		
		case 3:
		printf("you have chosen the third menu");
		
		break;
		
		default:
		for (uint8_t i = 0; i < 11; i++){
			printf("\r\n");
		}
			printf("Start Menu\r\n");
			printf("1 = Modes \r\n");
			printf("2 = Data \r\n");
			printf("3 = Configure address\r\n");
			start_var = compareCommands(command,choicearray,3);
			break;
		}
	}
	
void modesMenu(){
	switch (modes_var)
	{
	case 1:
	printf("Automatic speed activated\r\n");
	auto_flag = 1;
	modes_var=255;
		break;
	case 2:
	manualMenu();
		break;
	case 3:
	printf("Additional\r\n");
		break;
	case 4:
	printf("Going back ->\r\n");
	start_var= 255;
	break;
	
	default:
	for (uint8_t i = 0; i < 10; i++){
		printf("\r\n");
	}
	printf("Start Menu > Modes\r\n");
	printf("1 = Automatic Speed\r\n");
	printf("2 = Manual Speed\r\n");
	printf("3 = Additional\r\n");
	printf("4 = Go Back\r\n");
		break;
	}
}
void manualMenu(){
	switch (manual_var)
	{
		case 1:
		printf("Slow speed activated\r\n");
		auto_flag = false;
		speed= 30;
		manual_var=255;
		break;
		case 2:
		printf("Medium speed activated\r\n");
		auto_flag = false;
		speed=60;
		manual_var=255;
		
		break;
		case 3:
		printf("Fast speed activated\r\n");
		auto_flag = false;
		speed=90;
		manual_var=255;
		break;
		
		case 4:
		printf("Enter Percentage\r\n");
		printf("1 = Go Back");
		auto_flag = false;
		percentageVifte();
		
		break;
		
		case 5:
		printf("Going back->\r\n");
		modes_var=255;
		break;
		
		default:
		for (uint8_t i = 0; i < 8; i++){
			printf("\r\n");
		}
		manual_var = compareCommands(command,choicearray,5);
		printf("Start Menu > Modes > Manual speed\r\n");
		printf("1 = Slow\r\n");
		printf("2 = Medium\r\n");
		printf("3 = Fast\r\n");
		printf("4 = Percentage\r\n");
		printf("5 = Go Back\r\n");
	
		
		
		
		break;
	}
}

void percentageVifte(){
	// Convert the entire command array to an integer
	percentage_val = atoi(command);

	// Alternatively, using strtol for better error handling
	char* endptr;
	percentage_val = (int)strtol(command, &endptr, 10);

	// Check if conversion was successful
	if (*endptr != '\0') {
		// Conversion failed
		printf("Error: Invalid input\n");
		// Handle error here
		} else {
		// Conversion successful
		// Use percentage_val
		
		printf("Percentage value: %d\n", percentage_val);
	}

	if (compareCommands(command, choicearray, 5) == 1){
		manual_var = 255;
	}
}

void automaticspeed(){
	if (auto_flag)
	{
		//skjekker termistor og setter hastigheten etter det
		;
	}
}


switch (fan_var)
{
case 1:
	speed_controll_0(percentage_val);
	break;
case 2:
	speed_controll_1(percentage_val);
	break;
case 3:
	speed_controll_2(percentage_val);
	break;
case 4:
	speed_controll_3(percentage_val);	
	break;
case 5:
	speed_controll_4(percentage_val);
	break;
case 6:
	speed_controll_5(percentage_val);
	break;
case 7:
	speed_controll_6(percentage_val);
	break;
case 8:
	speed_controll_7(percentage_val);
	break;
default:
printf(("Choose your fan\r\n" ))
printf(("1 = Fan 1"));
printf(("2 = Fan 2"));
printf(("3 = Fan 3"));
printf(("4 = Fan 4"));
printf(("5 = Fan 5"));
printf(("6 = Fan 6"));
printf(("7 = Fan 7"));
printf(("8 = Fan 8"));
printf(("9 = Go Back->"));
fan_var = compareCommands(command,choicearray,8);
if (compareCommands(command, choicearray, 5) == 1){
	manual_var = 255;
}
}
