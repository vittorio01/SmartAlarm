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

/* settings interface */
void settingsView(Graphics_Context *gc);        //main settings code

/* clock interface */
void clockView(Graphics_Context *gc);           //main clock code

void initClockView(Graphics_Context *gc);       //init all the color for the clock view
void drawTime(Graphics_Context *gc);            //draw the current time on the display
void drawDate(Graphics_Context *gc);            //draw the current date on the display

/* clock variables */
static volatile RTC_C_Calendar currentTime;     // current time updated by the RTC's IRQ
static volatile uint8_t updateTime;             // flag that tell to update the time on the display (!=0 need update)
static volatile uint8_t updateDate;             // same of updateTime but for the date


#endif /* MODULES_CLOCK_SYSTEM_CLOCK_H_ */
