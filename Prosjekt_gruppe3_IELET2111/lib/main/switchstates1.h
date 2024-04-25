/*
 * switchstates1.h
 *
 * Created: 11.04.2024 15:44:04
 *  Author: Meg
 */ 


#ifndef SWITCHSTATES1_H_
#define SWITCHSTATES1_H_
void fan_choice();



//prototypes for the switch case
int automaticspeed();
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
uint8_t fanspeed_val1;
uint8_t read_val;

 //could set as exter

  //boll for keeping track of one command-each time speed is set

int percentage_val;  //percentage speed for the fans

static char *choicearray[9]={"1","2","3","4","5","6","7","8","9"
}; //command array for the different choices in the individual switch cases

#endif /* SWITCHSTATES1_H_ */
