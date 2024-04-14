/*
 * eeprommem.c
 *
 * Created: 14.04.2024 19:56:18
 *  Author: Meg
 */ 


void eeprom_check_ready(){
	while(1){
		if (eeprom_is_ready()){
			break;
			}else{
			;
		}
	}
}

void avrage_rpm(int current_rpm, uint8_t current_adress, int store_rpm, uint8_t fan_number ){ //100 iterasjoner for å ikke eeprom
	if(write_eeprom_flag){
	current_rpm= rpm_reader(fan_number);
	i++;
	store_rpm = store_rpm + current_rpm;
	if (i>100){// takes in 1 point every 100 points
		eeprom_check_ready(); // cheks if eeprom is ready
		int avrage_rpm_val = store_rpm/i // avrage of rpms
		eeprom_write_byte(current_adress,byte);
		i=0
		store_rpm = 0
		current_adress++;
	}
	}
}
}

write_struct2_eeprom(int write_structrpm,int current_adress){ //takes in struct and address of the unique fans
	uint8_t struct_size = sizeof(write_structrpm);  // size of the struct
	
	eeprom_check_ready(); // check if ready to write
	
	eeprom_update_block((void*) &write_structrpm,(void*) &current_adress, struct_size); //saves the struct 2 eeprom
	current_adress++;
}





uint8_t read_data_rpm_eeprom(uint8_t cur_adress, uint8_t start_address){
	uint8_t byte = 0;
	uint8_t len = cur_adress - start_address; //finds the length of all adresses

		eeprom_check_ready();

		for (uint8_t i = 0; i <len; i++){ 
			byte = eeprom_read_byte(i + start_address); // reads the rpm
			
			printf("Fanspeed nr %u : %u", i, byte);  // prints the value of the current adresses
			printf("\r\n");
		}
	return sizeof(array); //size of stored data, how many individual adresses stored
}


