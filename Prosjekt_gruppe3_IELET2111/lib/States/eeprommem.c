/*
 * eeprommem.c
 *
 * Created: 14.04.2024 19:56:18
 *  Author: Meg
 */ 
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
#include "pwm.h"


void eeprom_check_ready(){
	while(1){
		if (eeprom_is_ready()){
			break;
			}else{
			;
		}
	}
}

void eeprom_current_adress_boot(uint8_t current_adress,uint8_t n_count_adress,uint8_t start_adress){// this is a boot function,current_adress is updated under initialize
	
	n_count_adress = eeprom_read_byte(start_adress); //first adress contains number of adresses stored in
	current_adress = start_adress + n_count_adress ;
}

void avrage_rpm(int current_rpm, uint8_t current_adress, int store_rpm, uint8_t fan_numberm, uint8_t n_count_adress, uint8_t start_adress){ //100 iterasjoner for å ikke eeprom
	current_rpm = 10; //put in function or value that saves the current value
	i++;
	store_rpm = store_rpm + current_rpm;
	if (current_adress= start_adress + 31){ // each fan has eeprom space of 32 bytes, if current adress has reached 32 bytes
		current_adress= start_adress+1;  //set current adress to old adress, and write over old values
	}
	if (i>1000){// takes in 1 point every 100 points
		eeprom_check_ready(); // cheks if eeprom is ready
		int avrage_rpm_val = store_rpm/i; // average of rpm
		eeprom_write_byte(current_adress,avrage_rpm_val);
		i=0;
		store_rpm = 0;
		current_adress++;
		printf("current address updated");
		n_count_adress++;
	}
	}



write_struct2_eeprom(int write_structrpm,int current_adress){ //takes in struct and address of the unique fans
	uint8_t struct_size = sizeof(write_structrpm);  // size of the struct
	
	eeprom_check_ready(); // check if ready to write
	
	eeprom_update_block((void*) &write_structrpm,(void*) &current_adress, struct_size); //saves the struct 2 eeprom
	current_adress++;
}





void read_data_rpm_eeprom(uint16_t cur_adress, uint16_t start_address){
	uint8_t byte = 0;
	uint8_t len = cur_adress - start_address; //finds the length of all adresses

		eeprom_check_ready();

		for (uint8_t i = 1; i <=len; i++){ 
			byte = eeprom_read_byte(start_address+i); // reads the rpm
			
			printf("Fanspeed nr %u : %u", i,byte );  // prints the value of the current adresses
			printf("\r\n");
		}
}


void adress_space(){
	
}

