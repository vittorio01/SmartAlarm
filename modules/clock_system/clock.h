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
void settingsView(Graphics_Context *gc, volatile uint8_t *menuA);        //main settings code

void initSettingsView(Graphics_Context *gc);
void drawTitle(Graphics_Context *gc, char t[20]);
void drawMenu(Graphics_Context *gc);            //draw the menu
void drawCursor(Graphics_Context *gc, uint8_t position, uint8_t menu);    //draw the cursor at the n position depending in witch menu


/* clock interface */
void clockView(Graphics_Context *gc, volatile uint8_t *menuA);           //main clock code

void initClockView(Graphics_Context *gc);       //init all the color for the clock view
void drawTime(Graphics_Context *gc);            //draw the current time on the display
void drawDate(Graphics_Context *gc);            //draw the current date on the display
void drawSeconds(Graphics_Context *gc);         //draw the second clock image

/* clock variables */
static volatile RTC_C_Calendar currentTime;     // current time updated by the RTC's IRQ
static volatile uint8_t updateTime;             // flag that tell to update the time on the display (!=0 need update)
static volatile uint8_t updateDate;             // same of updateTime but for the date


#endif /* MODULES_CLOCK_SYSTEM_CLOCK_H_ */
