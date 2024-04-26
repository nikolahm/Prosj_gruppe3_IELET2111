/*
 * PWM.h
 *
 * Created: 25.04.2024 14:12:22
 *  Author: Meg
 */ 


#ifndef PWM_H_
#define PWM_H_


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


#endif /* PWM_H_ */
