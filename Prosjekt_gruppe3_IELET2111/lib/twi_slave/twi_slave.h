/*
 * twi_slave.h
 *
 * Created: 4/19/2024 10:08:23 AM
 *  Author: nicol
 */ 


#ifndef TWI_SLAVE_H_
#define TWI_SLAVE_H_

void twi_master_init_aht10(void);
uint8_t read_ath10_data(uint8_t mesurments);


#endif /* TWI_SLAVE_H_ */
