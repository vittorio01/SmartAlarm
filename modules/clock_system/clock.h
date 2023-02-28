#ifndef MODULES_CLOCK_SYSTEM_CLOCK_H_
#define MODULES_CLOCK_SYSTEM_CLOCK_H_

#include <modules/hardware/hardware.h>
#include <modules/ringtones_manager/ringtones_manager.h>
#include <modules/activities_launcher/activities.h>
#include "modules/hardware/hardware.h"
#include <stdio.h>
#include <string.h>

/* tests */
void testJoy(Graphics_Context *gc);

/* clock interface */
void initClockView(Graphics_Context *gc);       //init all the color for the clock view
void drawTime(Graphics_Context *gc);            //draw the current time on the display
void drawDate(Graphics_Context *gc);            //draw the current date on the display



#endif /* MODULES_CLOCK_SYSTEM_CLOCK_H_ */
