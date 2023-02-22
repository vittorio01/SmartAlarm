#include "msp.h"
#include "modules/clock_system/clock.h"
#include <modules/hardware/hardware.h>

typedef enum {GAME, CLOCK} running_activity;  // define witch main part of the program is running

typedef struct joystick {
    uint_fast16_t joyXvalue;
    uint_fast16_t joyYvalue;
}joystick;

joystick adcJoy;

/* GLOBAL VARIABLES */
running_activity current_activity = CLOCK;

void main(void) {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
}

//end
