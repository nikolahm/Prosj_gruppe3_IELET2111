/*
 * switchstates.c
 *
 * Created: 11.04.2024 15:40:59
 *  Author: Meg
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
void speed_controll_0(int i){i++;}
void speed_controll_1(int i){i++;}
void speed_controll_2(int i){i++;}
void speed_controll_3(int i){i++;}
void speed_controll_4(int i){i++;}
void speed_controll_5(int i){i++;}
void speed_controll_6(int i){i++;}
void speed_controll_7(int i){i++;}


void startMenu(){
	switch (start_var)
	{
		case 1:
		
		modesMenu();
		
		break;
		
		case 2:
		dataMenu();
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
	automaticspeed();
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
		modes_var = compareCommands(command,choicearray,5);
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
		auto_flag = false;
		if (set_speed_flag == true)
		{
			fan_choice();
			
		}else{ percentageVifte();
			printf("Enter Percentage\r\n");
			printf("1 = Go Back\r\n");
		}
		
		
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

void percentageVifte() {
	// Convert the entire command array to an integer
	percentage_val = atoi(command);

	// Alternatively, using strtol for better error handling
	char* endptr;
	percentage_val = (int) strtol(command, &endptr, 10);

	// Check if conversion was successful
	if (*endptr != '\0') {
		// Conversion failed
		printf("Error: Invalid input\n");
		// Handle error here
		} else {
		// Conversion successful
		// Use percentage_val
		printf("Percentage value: %d\n", percentage_val);

		// Check if the value is within the range of 0-100
		if (percentage_val >= 0 && percentage_val <= 100) {
			// Set a variable with the value of percentage_val
			fanspeed_val = percentage_val;
			set_speed_flag = true;
			} else {
			// Value is out of range
			printf("Error: Value too high, please select within the range of 0-100\n");
		}
	}
	if (compareCommands(command, choicearray, 5) == 1) {
		manual_var = 255;
	}
}


void fan_choice(){
	switch(fan_var)
	{
		case 1:
		printf("Fan 1 set to :",fanspeed_val);
		printf("\r\n");
		speed_controll_0(fanspeed_val);
		fan_var=255;
		break;
		case 2:
		printf("Fan 2 set to :",fanspeed_val);
		printf("\r\n");
		speed_controll_1(fanspeed_val);
		fan_var=255;
		break;
		case 3:
		printf("Fan 3 set to :",fanspeed_val);
		printf("\r\n");
		speed_controll_2(fanspeed_val);
		fan_var=255;
		break;
		case 4:
		printf("Fan 4 set to :",fanspeed_val);
		printf("\r\n");
		fan_var=255;
		speed_controll_3(fanspeed_val);
		set_speed_flag = false;
		break;
		case 5:
		printf("Fan 5 set to :",fanspeed_val);
		printf("\r\n");
		speed_controll_4(fanspeed_val);
		set_speed_flag = false;
		fan_var=255;
		break;
		case 6:
		printf("Fan 6 set to :",fanspeed_val);
		printf("\r\n");
		speed_controll_5(fanspeed_val);
		fan_var=255;
		break;
		case 7:
		printf("Fan 7 set to :",fanspeed_val);
		printf("\r\n");
		speed_controll_6(fanspeed_val);
		fan_var=255;
		break;
		case 8:
		printf("Fan 8 set to :",percentage_val);
		printf("\r\n");
		speed_controll_7(percentage_val);
		fan_var=255;
		break;
		case 9:
		manual_var = 255;
		break;
		default:
		printf(("Choose your fan\r\n" ));
		printf(("1 = Fan 1\r\n"));
		printf(("2 = Fan 2\r\n"));
		printf(("3 = Fan 3\r\n"));
		printf(("4 = Fan 4\r\n"));
		printf(("5 = Fan 5\r\n"));
		printf(("6 = Fan 6\r\n"));
		printf(("7 = Fan 7\r\n"));
		printf(("8 = Fan 8\r\n"));
		printf(("9 = Go Back->\r\n"));
		
		fan_var = compareCommands(command,choicearray,9);

		if (compareCommands(command, choicearray, 9) == 9){
			manual_var=255;
		}
		;
	}
}
void dataMenu(){
	switch (data_var)
	{
		case 1:
		printf("Read data is\r\n");
		
		break;
		
		case 2:
		printf("Updating is\r\n");
		break;
		
		case 3:
		printf("erase all data\r\n");
		break;
		
		case 4:
		printf("Going back\r\n");
		start_var = 255;
		break;
		
		default:
		printf("Start Menu > Data\r\n");
		printf("1 = Read data from the fans");
		printf("2 = Write data from the fans");
		printf("3 = Erase all data");
		printf("4 = Go Back->");
		data_var = compareCommands(command,choicearray,4);
	}
}

void automaticspeed(){
	if (auto_flag)
	{
		//skjekker termistor og setter hastigheten etter det
		;
	}
}


