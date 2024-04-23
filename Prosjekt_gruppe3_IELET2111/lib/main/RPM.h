/*
 * RPM.h
 *
 * Created: 21.04.2024 15:28:54
 *  Author: Meg
 */ 


#ifndef RPM_H_
#define RPM_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

//volatile int pulseCount = 0;
volatile long signal_pulse;
volatile long signal_period;
int frequency;
uint16_t RPM;
float dutycycle;
void TCB0_init(void);
void EVSYS_init();
int RPMstuff(void);




#endif /* RPM_H_ */
