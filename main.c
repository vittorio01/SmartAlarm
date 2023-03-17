#include "msp.h"
#include "modules/clock_system/clock.h"
#include <modules/hardware/hardware.h>

Graphics_Context g_sContext; // Graphic library context
Graphics_Context *gc = &g_sContext;


void main(void) {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	initHardware(gc);   //initialize all the hardware
	combo_master_start(gc);
	while (true) {
	    PCM_gotoLPM0();
	}
	/* define which menu show on the display
	 * 0 = clock view
	 * 1 = settings view
	 * 2 = time settings
	 * 3 = date settings
	 */
	volatile uint8_t menuActive = 0;
	volatile uint8_t alarmOn = 0;

	while(1){
	    switch(menuActive) {
	        case 0: clockView(gc, &menuActive, &alarmOn); break;
	        case 1: settingsView(gc, &menuActive); break;
	        case 2: timeSettView(gc, &menuActive); break;
	        case 3: alarmSettView(gc, &menuActive); break;
	    }
	    if(alarmFired == 1){
	        GPIO_toggleOutputOnPin(RGB_LED_RED_PORT, RGB_LED_RED_PIN);
            int i;
            for(i=0; i<1000;i++);   //big delay, slower incrementation
            GPIO_toggleOutputOnPin(RGB_LED_RED_PORT, RGB_LED_RED_PIN);

	        //run the game and the ringtones
	        alarmFired = 0;
	    }
	}
}

//end
