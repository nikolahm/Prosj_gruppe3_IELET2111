/*
 * statemachine.h
 *
 * Created: 10.04.2024 15:10:01
 *  Author: Meg
 */ 


#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU*64 / (16*(float)BAUD_RATE )) + 0.5)
#define MAX_COMMAND_LEN 10
#define NUMBER_OF_COMMANDS 8
#define CR 0x0D // ’\r’
#define LF 0x0A // ’\n’

//prototypes for the switch case
void automaticspeed();
void percentageVifte();
void startMenu();
void modesMenu();
void manualMenu();
//variables for the switch cases
uint8_t start_var;
uint8_t modes_var;
uint8_t manual_var;
uint8_t fan_var;
//percentage speed for the fans
int percentage_val;

char command [ MAX_COMMAND_LEN ]; // max lenght 
bool auto_flag;
int speed;
uint8_t index = 0;
uint8_t data_ready_flag= 0;

char c; //interupt variable for uart in loop
volatile char recived; //interupt variable for uart
// Prototypes for uart
void USART3_init ( void );
void USART3_sendChar ( char c);
static int USART3_printChar ( char c, FILE * stream );
void USART3_sendString ( char * str );
uint8_t USART3_read ();

uint8_t compareCommands ( char* src,char* arrays[],uint8_t array_size);
uint8_t case_choice(char*src,char choice);

// Setting up FDEV_SETUP_STREAM to use USART3_printChar
static FILE USART_stream = FDEV_SETUP_STREAM ( USART3_printChar , NULL ,_FDEV_SETUP_WRITE );
// Array of commands to compare to




#endif /* STATEMACHINE_H_ */
