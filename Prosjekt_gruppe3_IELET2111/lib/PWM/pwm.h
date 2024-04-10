#ifndef PWM_H
#define PWM_H

#include <inttypes.h>

void TCA0_init(void);
void TCA1_init(void);
void PORT_init(void);
void speed_controll_0(uint8_t persentage);
void speed_controll_1(uint8_t persentage);
void speed_controll_2(uint8_t persentage);
void speed_controll_3(uint8_t persentage);
void speed_controll_4(uint8_t persentage);
void speed_controll_5(uint8_t persentage);
void speed_controll_6 (uint8_t persentage);
void speed_controll_7 (uint8_t persentage);


#endif // PWM_H
