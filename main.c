#include "msp.h"
#include "modules/clock_system/clock.h"
#include "modules/activities_launcher/activities/combo_master/combo_master.h"
#include <modules/hardware/hardware.h>

Graphics_Context g_sContext; // Graphic library context
Graphics_Context *gc = &g_sContext;


void main(void) {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	initHardware(gc);   //initialize all the hardware
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
	        start_ringtone(0,5);

	        clearScreen(gc);
	        char* title[] = {"WAKE UP!"};
	        printTitleMessage(title,TITLE_DIMENSION,gc);

	        while (!buttonsPressed.b1 && !buttonsPressed.b1 && !buttonsPressed.jb) {
	            generate_wait(100);
	        }
	        stop_ringtone();
	        resetButtonsState();
	        while(launch_game(gc)!=TASK_COMPLETED) {
	            start_ringtone(0,5);
                while (!buttonsPressed.b1 && !buttonsPressed.b1 && !buttonsPressed.jb) {
                    generate_wait(100);
                }
                stop_ringtone();
                resetButtonsState();
	        }

	        //run the game and the ringtones
	        alarmFired = 0;
	    }
	}
}

//end
