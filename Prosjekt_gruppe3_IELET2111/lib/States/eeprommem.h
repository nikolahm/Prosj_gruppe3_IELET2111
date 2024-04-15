
/*
 * eeprommem.h
 *
 * Created: 12.04.2024 11:13:52
 *  Author: Meg
 */ 


#ifndef EEPROMMEM_H_
#define EEPROMMEM_H_

	//the starting adress of the fans, these start adresses contains information on how many of the adresses is ocuupied
static uint16_t start_fan_adress1= 0x1400;
static uint16_t start_fan_adress2= 0x1430;
static uint16_t start_fan_adress3= 0x1460;
static uint16_t start_fan_adress4= 0x1490;
static uint16_t start_fan_adress5= 0x14C0;
static uint16_t start_fan_adress6= 0x14F0;
static uint16_t start_fan_adress7= 0x1520;
static uint16_t start_fan_adress8= 0x1550;



static uint16_t current_fan_adress1= 0x1401; //
static uint16_t current_fan_adress2= 0x1431;
static uint16_t current_fan_adress3= 0x1461;
static uint16_t current_fan_adress4= 0x1491;
static uint16_t current_fan_adress5= 0x14C1;
static uint16_t current_fan_adress6= 0x14F1;
static uint16_t current_fan_adress7= 0x1521;
static uint16_t current_fan_adress8= 0x1551;

static uint16_t n_count_adress1=1;
static uint16_t n_count_adress2=1;
static uint16_t n_count_adress3=1;
static uint16_t n_count_adress4=1;
static uint16_t n_count_adress5=1;
static uint16_t n_count_adress6=1;
static uint16_t n_count_adress7=1;
static uint16_t n_count_adress8=1;



static int i = 0;
int store_rpm1;
int store_rpm2;
int store_rpm3;
int store_rpm4;
int store_rpm5;
int store_rpm6;
int store_rpm7;
int store_rpm8;
static bool write_eeprom_flag = false; 


typedef struct{
	uint8_t rpm;
	}config_t; 




#endif /* EEPROMMEM_H_ */
