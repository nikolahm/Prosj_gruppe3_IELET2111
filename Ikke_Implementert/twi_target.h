/*
* twi_target .h
*
* Created : 29.03.2023 11:48:01
* Author : crfosse
*/
# ifndef TWI_TARGET_H_
# define TWI_TARGET_H_
# include <stdbool.h>
# include <stdint.h>
// If defined , internal pullup resistors will be used
# define TWI_ENABLE_PULLUPS
/**
* @brief This function initiates the TWI target with a specified address .
*
* @param address The desired address of the target .
*/
void TWI_initClient ( uint8_t address );
/**
* @brief This function initiates the I/O pins used by the TWI .
*/
void TWI_initPins ( void );
/**
* @brief Assigns the function to call when a byte is written to this device
*
* @param onWrite a function with a uint8_t data parameter for handling received data .
*/
void TWI_assignByteWriteHandler ( void (* onWrite )( uint8_t ));
/**
* @brief Assigns the function to call when a byte is requested from this device
*
* @param onRead a function that returns a uint8_t value to be transmitted .
*/
void TWI_assignByteReadHandler ( uint8_t (* onRead )( void ) );
/**
* @brief Assigns the function to call when a stop condition occurs on the I2C Bus.
*/
void TWI_assignStopHandler ( void (* onStop )( void ));
# endif /* TWI_TARGET_H_ */
