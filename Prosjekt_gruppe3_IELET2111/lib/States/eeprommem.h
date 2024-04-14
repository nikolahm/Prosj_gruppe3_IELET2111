/*
 * eeprommem.h
 *
 * Created: 12.04.2024 11:13:52
 *  Author: Meg
 */ 


#ifndef EEPROMMEM_H_
#define EEPROMMEM_H_
uint16_t start_fan_adress1= 0x1400;
uint16_t start_fan_adress2= 0x1430;
uint16_t start_fan_adress3= 0x1460;
uint16_t start_fan_adress4= 0x1490;
uint16_t start_fan_adress5= 0x14C0;
uint16_t start_fan_adress6= 0x14F0;
uint16_t start_fan_adress7= 0x1520;
uint16_t start_fan_adress8= 0x1550;

uint16_t current_fan_adress1=	;
uint16_t current_fan_adress2=   ;
uint16_t current_fan_adress3=   ;
uint16_t current_fan_adress4=   ;
uint16_t current_fan_adress5=   ;
uint16_t current_fan_adress6=   ;
uint16_t current_fan_adress7=   ;
uint16_t current_fan_adress8=   ;

int i;
int store_rpm1;
int store_rpm2;
int store_rpm3;
int store_rpm4;
int store_rpm5;
int store_rpm6;
int store_rpm7;
int store_rpm8;
bool write_eeprom_flag = false; 

void avrage_rpm();
typedef struct{
	uint8_t rpm;
	}config_t; 




#endif /* EEPROMMEM_H_ */
