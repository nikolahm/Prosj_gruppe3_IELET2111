
#ifndef EEPROMMEM_H_
#define EEPROMMEM_H_

//the starting adress of the fans, these start adresses contains information on how many of the adresses is ocuupied
static const uint16_t start_fan_adress1= 0x1400;
static const uint16_t start_fan_adress2= 0x1430;
static const uint16_t start_fan_adress3= 0x1460;
static const uint16_t start_fan_adress4= 0x1490;
static const uint16_t start_fan_adress5= 0x14C0;
static const uint16_t start_fan_adress6= 0x14F0;
static const uint16_t start_fan_adress7= 0x1520;
static const uint16_t start_fan_adress8= 0x1550;
//the new adress to write on, so old values are not overwritten
//typedef struct  current_adress_struct
//{
extern volatile uint16_t current_fan_adress1;
extern volatile uint16_t current_fan_adress2;
extern volatile uint16_t current_fan_adress3;
extern volatile uint16_t current_fan_adress4;
extern volatile uint16_t current_fan_adress5;
extern volatile uint16_t current_fan_adress6;
extern volatile uint16_t current_fan_adress7;
extern volatile uint16_t current_fan_adress8;
//}curadrstrct;
//counts the total adresses occupied by each fan. max of 32 adresses each fan
//typedef struct n_count_struct
//{
extern volatile uint16_t n_count_adress1;
extern volatile uint16_t n_count_adress2;
extern volatile uint16_t n_count_adress3;
extern volatile uint16_t n_count_adress4;
extern volatile uint16_t n_count_adress5;
extern volatile uint16_t n_count_adress6;
extern volatile uint16_t n_count_adress7;
extern volatile uint16_t n_count_adress8;
//}ncntstrct
 static volatile uint16_t i = 0;
//typedef struct store_rpm_struct 
//{
// storing avrage information on fans
extern uint32_t store_rpm1;
extern uint32_t store_rpm2;
extern uint32_t store_rpm3;
extern uint32_t store_rpm4;
extern uint32_t store_rpm5;
extern uint32_t store_rpm6;
extern uint32_t store_rpm7;
extern uint32_t store_rpm8;

//prototype
void average_rpm(int *current_rpm,volatile uint16_t *current_address,volatile uint16_t *store_rpm,volatile uint16_t *n_count_address,const uint16_t *start_address);

uint8_t fanspeed1;
static bool write_eeprom_flag= true; //debugging variable

#endif /* EEPROMMEM_H_ */
 /* EEPROMMEM_H_ */
