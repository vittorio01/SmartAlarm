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

/* icons */
extern const tImage CLOCK_18BPP_UNCOMP;
extern const tImage CLOCK_28BPP_UNCOMP;
extern const tImage CLOCK_38BPP_UNCOMP;
extern const tImage CLOCK_48BPP_UNCOMP;
extern const tImage CURSOR_R1BPP_UNCOMP;
extern const tImage CURSOR_UP1BPP_UNCOMP;
extern const tImage CURSOR_DOWN1BPP_UNCOMP;
extern const tImage ALARM_ON8BPP_UNCOMP;
extern const tImage ALARM_OFF8BPP_UNCOMP;

/* settings interface */
void settingsView(Graphics_Context *gc, volatile uint8_t *menuA);        //main settings code

void initSettingsView(Graphics_Context *gc);
void drawTitle(Graphics_Context *gc, char t[20]);
void drawMenu(Graphics_Context *gc);            //draw the menu

/* alarm settings interface */
void alarmSettView(Graphics_Context *gc, volatile uint8_t *menuA);       // main time settings code

void initAlarmSettView(Graphics_Context *gc);
void drawAlarmMenu(Graphics_Context *gc);

/* time settings interface */
void timeSettView(Graphics_Context *gc, volatile uint8_t *menuA);       // main time settings code

void initTimeSettView(Graphics_Context *gc);
void drawTimeMenu(Graphics_Context *gc);


/* clock interface */
void clockView(Graphics_Context *gc, volatile uint8_t *menuA, uint8_t *alarmOn);           //main clock code

void initClockView(Graphics_Context *gc, uint8_t alarmOn);       // init all the color for the clock view
void drawTime(Graphics_Context *gc, RTC_C_Calendar t);            // draw the current time on the display
void drawDate(Graphics_Context *gc, RTC_C_Calendar time);            // draw the current date on the display
void drawSeconds(Graphics_Context *gc);         // draw the second clock image

void IRQdrawClock(void);                        // IRQ of the 1s timer interrupt
void drawClock(Graphics_Context *gc);           // draw the clock on the top left part of the screen
void drawAlarm(Graphics_Context *gc, uint8_t alarmOn);  // draw the alarm icon


/* clock variables */
static volatile RTC_C_Calendar currentTime;     // current time updated by the RTC's IRQ
static volatile RTC_C_Calendar alarmTime;
static volatile uint8_t updateTime;             // flag that tell to update the time on the display (!=0 need update)
static volatile uint8_t updateDate;             // same of updateTime but for the date
static volatile uint8_t updateClockImage;       // same of updateTime but for the clock image
static volatile uint8_t clockImage;             // define witch clock image

/* general functions */
#define AXIS_X 0
#define AXIS_Y 1
void getCursorPosition(uint8_t max, uint8_t *cursor,uint8_t *updateCursor, uint8_t *up, uint8_t *down, joystick joy, uint8_t axis);  // change cursor position
void drawCursor(Graphics_Context *gc, uint8_t position, uint8_t menu);    //draw the cursor at the n position depending in witch menu

#endif /* MODULES_CLOCK_SYSTEM_CLOCK_H_ */
