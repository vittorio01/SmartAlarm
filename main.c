#include "msp.h"
#include "modules/clock_system/clock.h"
#include <modules/hardware/hardware.h>

Graphics_Context g_sContext; // Graphic library context
Graphics_Context *gc = &g_sContext;
uint8_t menuActive = 0;     //define which menu show on the display

void main(void) {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	initHardware(gc);   //initialize all the hardware

	while(1){
	    switch(menuActive) {
	        case 0: clockView(gc); break;
	        case 1: settingsView(gc); break;
	    }
	}

}

//end
