/*
 * twi_slave.h
 *
 * Created: 4/19/2024 10:08:23 AM
 *  Author: nicol
 */ 


#ifndef TWI_AHT10_H_
#define TWI_AHT10_H_

void twi_master_init_aht10(void);
uint8_t read_aht10_data(uint8_t mesurments);


#endif /* TWI_AHT10_H_ */