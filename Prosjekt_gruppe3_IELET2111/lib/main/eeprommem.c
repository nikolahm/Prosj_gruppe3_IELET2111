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
#include "PWM.h"
#include "RPM.h"

 volatile uint16_t current_fan_adress1;
 volatile uint16_t current_fan_adress2;
 volatile uint16_t current_fan_adress3;
 volatile uint16_t current_fan_adress4;
 volatile uint16_t current_fan_adress5;
 volatile uint16_t current_fan_adress6;
 volatile uint16_t current_fan_adress7;
 volatile uint16_t current_fan_adress8;
 
  volatile uint16_t n_count_adress1=1;
  volatile uint16_t n_count_adress2=1;
  volatile uint16_t n_count_adress3=1;
  volatile uint16_t n_count_adress4=1;
  volatile uint16_t n_count_adress5=1;
  volatile uint16_t n_count_adress6=1;
  volatile uint16_t n_count_adress7=1;
  volatile uint16_t n_count_adress8=1;
  
	uint32_t store_rpm1;
   uint32_t store_rpm2;
   uint32_t store_rpm3;
   uint32_t store_rpm4;
   uint32_t store_rpm5;
   uint32_t store_rpm6;
   uint32_t store_rpm7;
   uint32_t store_rpm8;
  

  // only write once
   



void eeprom_check_ready(){
	while(1){
		if (eeprom_is_ready()){
			break;
			}else{
			;
		}
	}
}

void eeprom_current_adress_boot(volatile uint16_t *current_adress,volatile uint16_t *n_count_adress,const uint16_t *start_adress) {
	*n_count_adress= eeprom_read_byte((*start_adress)); // Read the value from EEPROM and store it in the memory location pointed to by n_count_adress
	printf("n_count adress is: %d\r\n", *n_count_adress);
	*current_adress = *start_adress + *n_count_adress; // Calculate the current address and store it in the memory location pointed to by current_adress
	if(*n_count_adress>30){
		printf("storage is full, rewriting will commence\r\n");
	}
}


void average_rpm(int *current_rpm,volatile uint16_t *current_address,volatile uint16_t *store_rpm,volatile uint16_t *n_count_address,const uint16_t *start_address) {
	if (1) {
		fanspeed_val= automaticspeed();
		
		uint16_t RPM_output1 = RPM_value(RPM);
		uint16_t RPM_INPUT1 = 202.82118538941248 - 98.6784062283774*(fanspeed_val) + 6.214541290707817 * pow((fanspeed_val), 2) + 0.00901579323430356 * pow((fanspeed_val), 3) + -0.0018046531131196354 * pow((fanspeed_val), 4) + 0.00001879112425079804 * pow((fanspeed_val), 5) -5.581980709961264 *pow(10, -8) * pow((fanspeed_val), 6);
		
// 				printf("fanspeedvalue\r\n");
// 				printf("%d\n",RPM_INPUT1);
// 				printf("tacometer\r\n");
// 				printf("%d\n\n",RPM_output1);
				
		//(*current_rpm)
		uint16_t pred_var= (((float)(RPM_INPUT1-RPM_output1))/((float)(RPM_INPUT1)))*100;
// 		
// 		printf("difference: ");
// 		printf("%d\n",pred_var);
		i++;
		(store_rpm1) += pred_var;
		uint16_t printvar=(store_rpm1);
// 		printf("%d\n",printvar);
// 		
		// Check if current address exceeds maximum address
		if ((*current_address) >= ((*start_address) + 29)) {
			(*current_address) = (*start_address) + 1; // Reset current address
		}
// 		printf("count: ");
// 		printf("%d\n",i);
		if (i > 100) {
			eeprom_check_ready(); // Check if EEPROM is ready
			
			int average_rpm_val = (*store_rpm) / i; // Calculate average of RPM
			eeprom_update_byte((volatile uint16_t)(*current_address), average_rpm_val);
			i = 0;
			(*store_rpm) = 0;
			(*current_address)++;
			printf("Current address updated\r\n");
			//*eeprom_write_byte((*start_address), (*n_count_address));//
			printf("%d\r\n",average_rpm_val);
			(*n_count_address)++;
		}
		write_eeprom_flag = false;
	}
}



void write_struct2_eeprom(int write_structrpm,int current_adress){ //takes in struct and address of the unique fans
	uint8_t struct_size = sizeof(write_structrpm);  // size of the struct
	
	eeprom_check_ready(); // check if ready to write
	
	eeprom_update_block((void*) &write_structrpm,(void*) &current_adress, struct_size); //saves the struct 2 eeprom
	current_adress++;
}
void initialize_adresses(){
	eeprom_write_byte(&start_fan_adress1,1);
	eeprom_write_byte(&start_fan_adress2,1);
	eeprom_write_byte(&start_fan_adress3,1);
	eeprom_write_byte(&start_fan_adress4,1);
	eeprom_write_byte(&start_fan_adress5,1);
	eeprom_write_byte(&start_fan_adress6,1);
	eeprom_write_byte(&start_fan_adress7,1);
	eeprom_write_byte(&start_fan_adress8,1);
	eeprom_current_adress_boot(&current_fan_adress1,&n_count_adress1,&start_fan_adress1);
	eeprom_current_adress_boot(&current_fan_adress2,&n_count_adress2,&start_fan_adress2);
	eeprom_current_adress_boot(&current_fan_adress3,&n_count_adress3,&start_fan_adress3);
	eeprom_current_adress_boot(&current_fan_adress4,&n_count_adress4,&start_fan_adress4);
	eeprom_current_adress_boot(&current_fan_adress5,&n_count_adress5,&start_fan_adress5);
	eeprom_current_adress_boot(&current_fan_adress6,&n_count_adress6,&start_fan_adress6);
	eeprom_current_adress_boot(&current_fan_adress7,&n_count_adress7,&start_fan_adress7);
	eeprom_current_adress_boot(&current_fan_adress8,&n_count_adress8,&start_fan_adress8);
}




void read_data_rpm_eeprom(volatile uint16_t *cur_adress,const uint16_t *start_address,volatile uint16_t *n_count_adress){
	uint16_t byte = 0;
	uint16_t len = *cur_adress - *start_address; //finds the length of all adresses
	
	printf("number of occupied adresses is : ");
	printf("%u",(len));
	printf("\r\n");
		eeprom_check_ready();

		for (uint8_t i = 1; i <=len; i++){ 
			byte = eeprom_read_byte((*start_address)+i); // reads the rpm
			
			printf("Fanspeed nr %u : %u", i,byte );  // prints the value of the current adresses
			printf("\r\n");
		}
}


void adress_space_clear(){
	eeprom_write_byte(start_fan_adress1,1);
	eeprom_write_byte(start_fan_adress2,1);
	eeprom_write_byte(start_fan_adress3,1);
	eeprom_write_byte(start_fan_adress4,1);
	eeprom_write_byte(start_fan_adress5,1);
	eeprom_write_byte(start_fan_adress6,1);
	eeprom_write_byte(start_fan_adress7,1);
	eeprom_write_byte(start_fan_adress8,1);
	
}
