/*
 * switchstates.c
 *
 * Created: 11.04.2024 15:40:59
 *  Author: HS
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
#include "switchstates.h"
#include "eeprommem.h"
#include "PWM.h"
#include "RPM.h"
bool auto_flag= true; //activates temprature controlled speed and eeprom storing of data
bool set_speed_flag = false; // bool to keep track of writing speed to fan


void startMenu(){
	
	//automaticspeed();
	
			
	switch (start_var) //startmenu and its choices
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
			//prints choices
		printf("Start Menu\r\n");
		printf("1 = Modes \r\n");
		printf("2 = Data \r\n");
		printf("3 = Configure address\r\n");
		start_var = compareCommands(command,choicearray,3); //compares command to array of commads
		modes_var = 255;
		break;
		}
	
		}


void modesMenu(){
	switch (modes_var) //switch case for different types of speed-controlling
	{
		case 1:
		printf("Automatic speed activated\r\n");
		auto_flag = true; //automatic speed is set
		modes_var=255;
		break;
		case 2:
		manualMenu(); //manualspeed menu
		break;
		case 3:
		printf("Additional\r\n"); //not implemented
		break;
		case 4:
		printf("Going back ->\r\n"); // go back
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
		modes_var = compareCommands(command,choicearray,5); //compares command to command array
		manual_var=255;
		fan_var=255;
		
		break;
	}
}
void manualMenu(){
	switch (manual_var)
	{
		case 1://set speed manually
		auto_flag = false;
		if (set_speed_flag)
		{
			fan_choice(); //pick which fan to set the percentage speed to
			
		}else{ percentageVifte(); //pick speed
			printf("Enter Percentage\r\n"); 
			
		}
			
		break;
		
		case 2:
		printf("Going back->\r\n");
		modes_var=255;
		manual_var=255;
		break;
		
		default:
		for (uint8_t i = 0; i < 8; i++){
			printf("\r\n");
		}
		manual_var = compareCommands(command,choicearray,5); //compares command to command array
		printf("Start Menu > Modes > Manual speed\r\n");
		printf("1 = Percentage\r\n");
		printf("2 = Go Back\r\n");
		
	}
}

void percentageVifte() {
	// Convert the entire command array to an integer
	percentage_val = atoi(command);

	// use strtol better for errors
	char* endptr;
	percentage_val = (int) strtol(command, &endptr, 10);

	// Check if conversion was successful
	if (*endptr != '\0') {
		// Conversion failed
		printf("Error: Invalid input\n");
		// Handle error here
		} else {
		// Conversion successful
		// Check if the value is within the range of 0-100
		if (percentage_val >= 0 && percentage_val <= 100) {
			// Set a variable with the value of percentage_val
			printf("Percentage value: %d\n", percentage_val); //prints to user
			fanspeed_val = percentage_val;
			fanspeed_val1 = percentage_val;
			
			printf(percentage_val);
			
			set_speed_flag = true; //fanspeedchoice is activated
			} else {
			// Value is out of range
			printf("Error: Value out of range, please select within the range of 0-100\n");
		}
	}
	
}


void fan_choice(){ //choose which fan that the speed is set to
	switch(fan_var)
	{
		case 1:
		printf("Fan 1 set to :%d\r\n",percentage_val); 
		printf("\r\n");
		printf("Choose your next percentage:\r\n");
		speed_controll_0(percentage_val);
		
		printf(fanspeed_val);
		fan_var=255;
		set_speed_flag = false;
		break;
		
		case 2:
		printf("Fan 2 set to :%d\r\n",fanspeed_val);
		printf("\r\n");
		printf("Choose your next percentage:\r\n");
		speed_controll_1(fanspeed_val);
		set_speed_flag = false;
		fan_var=255;
		break;
		
		case 3:
		printf("Fan 3 set to :%d\r\n",fanspeed_val);
		printf("\r\n");
		printf("Choose your next percentage:\r\n");
		speed_controll_2(fanspeed_val);
		fan_var=255;
		set_speed_flag = false;
		break;
		
		case 4:
		printf("Fan 4 set to :%d\r\n",fanspeed_val);
		printf("\r\n");
		printf("Choose your next percentage:\r\n");
		fan_var=255;
		speed_controll_3(fanspeed_val);
		set_speed_flag = false;
		break;
		
		case 5:
		printf("Fan 5 set to :%d\r\n",fanspeed_val);
		printf("\r\n");
		printf("Choose your next percentage:\r\n");
		speed_controll_4(fanspeed_val);
		set_speed_flag = false;
		fan_var=255;
		break;
		
		case 6:
		printf("Fan 6 set to :%d\r\n",fanspeed_val);
		printf("\r\n");
		printf("Choose your next percentage:\r\n");
		speed_controll_5(fanspeed_val);
		set_speed_flag = false;
		fan_var=255;
		break;
		
		case 7:
		printf("Fan 7 set to :%d\r\n",fanspeed_val);
		printf("\r\n");
		printf("Choose your next percentage:\r\n");
		speed_controll_6(fanspeed_val);
		fan_var=255;
		set_speed_flag = false;
		break;
		
		case 8:
		printf("Fan 8 set to :%d\r\n",percentage_val);
		printf("\r\n");
		printf("Choose your next percentage:\r\n");
		speed_controll_7(percentage_val);
		fan_var=255;
		set_speed_flag = false;
		break;
		
		case 9:
		printf("Going Back->");
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
		
		fan_var = compareCommands(command,choicearray,9); //compares command to command array
	}
}
void dataMenu(){
	switch (data_var)
	{
		case 1:

		readeeprom(); //read pred-data on fans
		
		break;
		
		case 2:
		printf("erase all data\r\n");
		adress_space_clear(); //rewriting will commence
		data_var=255;
		break;
		
		case 3:
		printf("Going back\r\n");
		start_var = 255;
		break;
		
		default:
		printf("Start Menu > Data\r\n");
		printf("1 = Read data from the fans\r\n");
		printf("2 = Erase all data\r\n");
		printf("3 = Go Back->\r\n");
		data_var = compareCommands(command,choicearray,9);
	}	
}

int automaticspeed(){ //sets the speed of the fans with temprature data
	
	uint8_t setspeed = 0; //setmanual speed is false
   if (auto_flag) { //if autospeed is activated
	  
	   setspeed = (read_aht10_data(0)) * 8 - 150; // Linear interpolation to calculate speed
	   
	   if (!(setspeed < 100 && setspeed > 0)) {
		   setspeed = 0; // Set to default if speed is out of range
		  speed_controll_0(setspeed); //setspeed to zero
		   printf("ERROR: speed is set to zero\n");
		   printf("ERROR reading data from temprature sensor");
	   }
		speed_controll_0(setspeed); //setspeed
   }
   return setspeed; //returns value

   }


void readeeprom(){
	switch (read_val) //reads pred-value of each address occupied to specified fan
	{
	case 1:
	read_data_rpm_eeprom(&current_fan_adress1,&start_fan_adress1,&n_count_adress1);
	read_val=255;
		break;
	case 2 :
	read_data_rpm_eeprom(&current_fan_adress2,&start_fan_adress2,&n_count_adress2);
	read_val=255;
		break;
	case 3:
	read_data_rpm_eeprom(&current_fan_adress3,&start_fan_adress3,&n_count_adress3);
	read_val=255;
		break;
	case 4:
	read_data_rpm_eeprom(&current_fan_adress4,&start_fan_adress4,&n_count_adress4);
	read_val=255;
		break;
	case 5:
	read_data_rpm_eeprom(&current_fan_adress5,&start_fan_adress5,&n_count_adress5);
	read_val=255;
		break;
	case 6:
	read_data_rpm_eeprom(&current_fan_adress6,&start_fan_adress6,&n_count_adress6);
	read_val=255;
		break;
	case 7:
	read_data_rpm_eeprom(&current_fan_adress7,&start_fan_adress7,&n_count_adress7);
	read_val=255;
		break;
	case 8:
	read_data_rpm_eeprom(&current_fan_adress8,&start_fan_adress8,&n_count_adress8);
	read_val=255;
		break;
	case 9:
		printf("Going Back->\r\n");
		start_var=255;
		break;
	default:
	printf("1 = Fan 1\r\n");
	printf("2 = Fan 2\r\n");
	printf("3 = Fan 3\r\n");
	printf("4 = Fan 4\r\n");
	printf("5 = Fan 5\r\n");
	printf("6 = Fan 6\r\n");
	printf("7 = Fan 7\r\n");
	printf("8 = Fan 8\r\n");
	printf("9 = Go Back->\r\n");
	read_val=compareCommands(command,choicearray,9);


			
	}
}
