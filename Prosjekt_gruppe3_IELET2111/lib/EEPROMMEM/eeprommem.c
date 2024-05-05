#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h> //library from https://onlinedocs.microchip.com/pr/GUID-317042D4-BCCE-4065-BB05-AC4312DBC2C4-en-US-2/index.html?GUID-735C4A48-0970-4086-A5CA-89AC469956ED
#include "uart.h"
#include "switchstates.h"
#include "eeprommem.h"
#include "PWM.h"
#include "RPM.h"
//adresses for eeprom storage
 volatile uint16_t current_fan_adress1;
 volatile uint16_t current_fan_adress2;
 volatile uint16_t current_fan_adress3;
 volatile uint16_t current_fan_adress4;
 volatile uint16_t current_fan_adress5;
 volatile uint16_t current_fan_adress6;
 volatile uint16_t current_fan_adress7;
 volatile uint16_t current_fan_adress8;
 // variable holding each adresses active adress number
  volatile uint16_t n_count_adress1=1;
  volatile uint16_t n_count_adress2=1;
  volatile uint16_t n_count_adress3=1;
  volatile uint16_t n_count_adress4=1;
  volatile uint16_t n_count_adress5=1;
  volatile uint16_t n_count_adress6=1;
  volatile uint16_t n_count_adress7=1;
  volatile uint16_t n_count_adress8=1;
  //variables used for further development-store each avrage fan speed
uint32_t store_rpm1;
uint32_t store_rpm2;
uint32_t store_rpm3;
uint32_t store_rpm4;
uint32_t store_rpm5;
uint32_t store_rpm6;
uint32_t store_rpm7;
uint32_t store_rpm8;
  

  // only write once
   


//waits for eeprom
void eeprom_check_ready(){
	while(1){
		if (eeprom_is_ready()){
			break;
			}else{
			;
		}
	}
}



// function which saves the prediction value
void average_rpm(int *current_rpm,volatile uint16_t *current_address,volatile uint16_t *store_rpm,volatile uint16_t *n_count_address,const uint16_t *start_address) {
	if(!data_read){
		fanspeed_val= automaticspeed();
		//The fans output
		uint16_t RPM_output1 = RPM_value(RPM); 
		//the avr128db48 controll signal
		uint16_t RPM_INPUT1 = 202.82118538941248 - 98.6784062283774*(fanspeed_val) + 6.214541290707817 * pow((fanspeed_val), 2) + 0.00901579323430356 * pow((fanspeed_val), 3) + -0.0018046531131196354 * pow((fanspeed_val), 4) + 0.00001879112425079804 * pow((fanspeed_val), 5) -5.581980709961264 *pow(10, -8) * pow((fanspeed_val), 6);
	
		if ((RPM_output1>1000) && (RPM_INPUT1>1000) && (RPM_output1<13600)){
		
		//calculate difference between input and output signal
		long int pred_var = (int)(((float)(RPM_INPUT1 - RPM_output1) / (float)RPM_INPUT1) * 100);
		
		// if the calculation is not in range-used for debugging
		/*if (pred_var >= 100 || pred_var <0) {
		pred_var=0;
		} */

		i++;
		store_rpm1 += pred_var; //sums the value of difference to a store_rpm1
		pred_var=0;
	
		if (i > 20) {
			
			n_count_adress1 = eeprom_read_byte(start_fan_adress1); //reads number of occupied adresses
			current_fan_adress1= n_count_adress1 + start_fan_adress1; //configures the position of current adress
			
			if (current_fan_adress1>= (start_fan_adress1 + 29)) { //function that checks if the number of occupied adresses has reached its limit
				current_fan_adress1 = start_fan_adress1 + 1; // Reset current address
				n_count_adress1=1;
				eeprom_update_byte(start_fan_adress1,n_count_adress1); //resets for new write
				printf("updated address\n");
			}
		

			
			
			//eeprom_check_ready(); // Check if EEPROM is ready
			n_count_adress1++; //new count
			
			uint16_t average_rpm_val = ((float)store_rpm1) / i; // Calculate average of RPM
			
			printf("average difference is: %d\n", average_rpm_val); //prints to user

			eeprom_update_byte(current_fan_adress1, average_rpm_val);//store the new value

			uint16_t prinnow = eeprom_read_byte(current_fan_adress1); // reads and prints the value to the user-used as confirming write
			printf("the value printed to the address is: %d\n", prinnow);

			current_fan_adress1++; // Increment pointers correctly //new adress
			printf("Current address updated: %d\n", current_fan_adress1); //prints to user
			
			eeprom_update_byte(start_fan_adress1, n_count_adress1);//saves the current number of adresses occupied

			printf("Number of addresses occupied is: ");
			printf("%d\n", n_count_adress1); //prints number of adresses occupied
			store_rpm1 = 0; // Reset store_rpm
			average_rpm_val = 0; // Reset average_rpm_val
			i = 0; // Reset i
		}
		//write_eeprom_flag = false; // used for debugging
	}
	}
	}
	
//future expansion/impovement of code-instead of using a lot of variables-use struct-better memory allocation
void write_struct2_eeprom(int write_structrpm,int current_adress){ //takes in struct and address of the unique fans 
	uint8_t struct_size = sizeof(write_structrpm);  // size of the struct
	
	eeprom_check_ready(); // check if ready to write
	
	eeprom_update_block((void*) &write_structrpm,(void*) &current_adress, struct_size); //saves the struct 2 eeprom
	current_adress++;
}
void initialize_adresses(){ //sets the last address of every fan
	//adress_space_clear(); //manually resets adresses
	
	eeprom_current_adress_boot(&current_fan_adress1,&n_count_adress1,&start_fan_adress1);
	eeprom_current_adress_boot(&current_fan_adress2,&n_count_adress2,&start_fan_adress2);
	eeprom_current_adress_boot(&current_fan_adress3,&n_count_adress3,&start_fan_adress3);
	eeprom_current_adress_boot(&current_fan_adress4,&n_count_adress4,&start_fan_adress4);
	eeprom_current_adress_boot(&current_fan_adress5,&n_count_adress5,&start_fan_adress5);
	eeprom_current_adress_boot(&current_fan_adress6,&n_count_adress6,&start_fan_adress6);
	eeprom_current_adress_boot(&current_fan_adress7,&n_count_adress7,&start_fan_adress7);
	eeprom_current_adress_boot(&current_fan_adress8,&n_count_adress8,&start_fan_adress8);
}

void eeprom_current_adress_boot(volatile uint16_t *current_adress, volatile uint16_t *n_count_adress, const uint16_t *start_adress) {
	uint8_t byte = eeprom_read_byte(*start_adress); // reads from start adress-get number of occupied addresses
	printf("n_count adress is: %d\r\n", byte); //prints to user
	*n_count_adress = byte; //number is set to global variable
	
	uint16_t len = *start_adress + byte; // Calculate the current address
	
	*current_adress = len; // Update the value at the memory location pointed to by current_adress
	
	printf("current adress is: %d\r\n", *current_adress); //prints to user
	
	if (byte > 30) { //if storage is full, rewriting will commence
		printf("storage is full, rewriting will commence\r\n");
		eeprom_update_byte(*start_adress, 1); // reset for overwriting
	}
}



void read_data_rpm_eeprom(volatile uint16_t *cur_adress,const uint16_t *start_address,volatile uint16_t *n_count_adress){
	data_read = true; //stops writing to eeprom
	uint16_t byte = 0;
	uint8_t len =eeprom_read_byte(*start_address); //finds the number of adresses
	
	printf("number of occupied adresses is : "); //print to user
	printf("%u",(len));
	printf("\r\n");
		eeprom_check_ready();

		for (uint8_t i = 1; i <=len; i++){  //for lenght og occupied adresses
			byte = eeprom_read_byte((*start_address)+i); // reads the pred-value for each occupied adress
			
			printf("Difference nr %u : %u", i,byte );  // prints the value of the pred value
			printf("\r\n");
		}
		data_read=false; //writing can commence
}


void adress_space_clear(){ //starts rewriting
	eeprom_write_byte(start_fan_adress1,1);
	eeprom_write_byte(start_fan_adress2,1);
	eeprom_write_byte(start_fan_adress3,1);
	eeprom_write_byte(start_fan_adress4,1);
	eeprom_write_byte(start_fan_adress5,1);
	eeprom_write_byte(start_fan_adress6,1);
	eeprom_write_byte(start_fan_adress7,1);
	eeprom_write_byte(start_fan_adress8,1);
	
}
