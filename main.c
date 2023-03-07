#include "msp.h"
#include "modules/clock_system/clock.h"
#include <modules/hardware/hardware.h>

Graphics_Context g_sContext; // Graphic library context
Graphics_Context *gc = &g_sContext;
/* define which menu show on the display
 * 0 = clock view
 * 1 = settings view
 * 2 = time settings
 * 3 = date settings
 */
volatile uint8_t menuActive = 0;

void main(void) {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	initHardware(gc);   //initialize all the hardware

	while(1){
	    switch(menuActive) {
	        case 0: clockView(gc, &menuActive); break;
	        case 1: settingsView(gc, &menuActive); break;
	    }
	}

}

//end
