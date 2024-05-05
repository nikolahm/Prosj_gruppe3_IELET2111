#ifndef RPM_H_
#define RPM_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

//volatile int pulseCount = 0;

int frequency;
uint16_t RPM;
float dutycycle;
void TCB0_init(void);
void EVSYS_init();
int RPMstuff(void);
int RPM_value(uint16_t var);




#endif /* RPM_H_ */
