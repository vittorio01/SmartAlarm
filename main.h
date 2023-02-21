#ifndef MAIN_H_
#define MAIN_H_


/* GLOBAL TYPES */
typedef enum {GAME, CLOCK}running_activity;  // define witch main part of the program is running

typedef struct joystick {
    uint_fast16_t joyXvalue;
    uint_fast16_t joyYvalue;
}joystick;


/* GLOBAL VARIABLES */
extern running_activity current_activity;
extern joystick adcJoy;

#endif /* MAIN_H_ */
