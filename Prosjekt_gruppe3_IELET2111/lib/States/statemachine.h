/*
 * switchstates1.h
 *
 * Created: 11.04.2024 15:44:04
 *  Author: Meg
 */ 


#ifndef SWITCHSTATES1_H_
#define SWITCHSTATES1_H_
void fan_choice();
void speed_controll_0();
void speed_controll_1();
void speed_controll_2();
void speed_controll_3();
void speed_controll_4();
void speed_controll_5();
void speed_controll_6();
void speed_controll_7();
void speed_controll_8();


//prototypes for the switch case
void automaticspeed();
void percentageVifte();
void startMenu();
void modesMenu();
void manualMenu();
//variables for the switch cases
uint8_t start_var;
uint8_t modes_var;
uint8_t manual_var;
uint8_t fan_var;
uint8_t data_var;
uint8_t fanspeed_val;
static bool set_speed_flag = false;
//percentage speed for the fans
int percentage_val;

static char *choicearray[9]={

	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9"
};





#endif /* SWITCHSTATES1_H_ */
