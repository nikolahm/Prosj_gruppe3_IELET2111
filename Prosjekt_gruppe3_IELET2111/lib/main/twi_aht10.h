/* twi_aht10.h
 *
 * Created: 22.04.2024 11:34:42
 *  Author: Meg
 */ 


#ifndef TWI_AHT10_H_
#define TWI_AHT10_H_
void twi_master_init_aht10(void);
uint8_t read_aht10_data(uint8_t mesurments);

#endif /* TWI_AHT10_H_ */
