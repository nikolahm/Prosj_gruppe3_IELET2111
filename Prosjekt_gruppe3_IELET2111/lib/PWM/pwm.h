#ifndef PWM_H
#define PWM_H

#include <inttypes.h>

void TCA0_init(void);
void PORT_init(void);
void speed_controll(uint8_t persentage);


#endif // PWM_H
