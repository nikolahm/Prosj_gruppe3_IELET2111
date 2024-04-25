/*
 * uart.h
 *
 * Created: 11.04.2024 15:30:52
 *  Author: Meg
 */ 


#ifndef UART_H_
#define UART_H_
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU*64 / (16*(float)BAUD_RATE )) + 0.5)
#define MAX_COMMAND_LEN 10
#define NUMBER_OF_COMMANDS 8
#define CR 0x0D // ’\r’
#define LF 0x0A // ’\n’
#include <stdbool.h>

volatile char recived; //interupt variable for uart
char command [ MAX_COMMAND_LEN ]; // max lenght
char c; //interupt variable for uart in loop

int speed;
static uint8_t index = 0;
static volatile uint8_t data_ready_flag= 0;

// Prototypes for uart
void USART3_init ( void );
void USART3_sendChar ( char c);
 int USART3_printChar ( char c, FILE * stream ); //defined used but not defined?
void USART3_sendString ( char * str );
uint8_t USART3_read ();

uint8_t compareCommands ( char* src,char* arrays[],uint8_t array_size);
uint8_t case_choice(char*src,char choice);

// Setting up FDEV_SETUP_STREAM to use USART3_printChar
static FILE USART_stream = FDEV_SETUP_STREAM ( USART3_printChar , NULL ,_FDEV_SETUP_WRITE ); //defined but not used
// Array of commands to compare to

#endif /* UART_H_ */
