#include "clock.h"


void testJoy(Graphics_Context *gc) { //only a test
    joystick adcJoy;    //joystic values

    adcJoy = getJoyValue();

    char joy[20];
    sprintf(joy, "x: %3d   y:%3d", (int) adcJoy.joyXvalue, (int) adcJoy.joyYvalue);
    Graphics_drawString(gc, (int8_t*) joy, sizeof(joy), 10, 20,OPAQUE_TEXT);
}

/* ALARM SETTINGS VIEW */
void alarmSettView(Graphics_Context *gc, volatile uint8_t *menuA){
    RTC_C_Calendar settedTime = currentTime;
    uint8_t cursor = 1;
    uint8_t updateCursor = 1;
    uint8_t up = 0;
    uint8_t down = 0;
    initAlarmSettView(gc);
    drawAlarmMenu(gc);

    uint8_t hours = RTC_C_convertBCDToBinary(settedTime.hours);
    uint8_t minutes = RTC_C_convertBCDToBinary(settedTime.minutes);
    joystick joy;
    startADCconversions();
    while(!buttonsPressed.jb){
        joy = getJoyValue();

        if(!(joy.joyYvalue<50 && joy.joyYvalue>-50)){
            int i;
            switch(cursor){
                case 1:
                    if(joy.joyYvalue>0){
                        hours = (hours + 1)%24;
                    }else{
                        if(hours-1 > 0){
                            hours = hours - 1;
                        }else{
                            hours = 23;
                        }
                    }
                    break;
                case 2:
                    if(joy.joyYvalue>0){
                        minutes = (minutes + 1)%60;
                    }else{
                        if(minutes-1 > 0){
                            minutes = minutes - 1;
                        }else{
                            minutes = 59;
                        }
                    }

                    break;
            }
            settedTime.hours = RTC_C_convertBinaryToBCD(hours);
            settedTime.minutes = RTC_C_convertBinaryToBCD(minutes);
            if(!(joy.joyYvalue<100 && joy.joyYvalue>-100)){
               for(i=0; i<10000;i++);   //small delay, faster incrementation
            }else{
               for(i=0; i<100000;i++);   //big delay, slower incrementation
            }
        }

        drawTime(gc, settedTime);
        getCursorPosition(2, &cursor, &updateCursor, &up, &down, joy, AXIS_X);
        if(updateCursor == 1){
            drawCursor(gc, cursor, *menuA);
            updateCursor = 0;
        }
    }
    alarmTime = settedTime;
    RTC_C_setCalendarAlarm(settedTime.minutes, settedTime.hours, RTC_C_ALARMCONDITION_OFF, RTC_C_ALARMCONDITION_OFF);
    *menuA = 0;
    buttonsPressed.jb = 0;
    stopADCconversions();
}

void initAlarmSettView(Graphics_Context *gc){
    resetButtonsState();
    Graphics_Rectangle fillRectangle;
    fillRectangle.xMin = 0;
    fillRectangle.xMax = 127;
    fillRectangle.yMin = 0;
    fillRectangle.yMax = 127;
    //color the entire frame of black
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_fillRectangle(gc, &fillRectangle);
    //set background black and the text/obj white
    Graphics_setBackgroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
}

void drawAlarmMenu(Graphics_Context *gc){
    #define TEXT_POSITION_X 35
    #define TEXT_POSITION_Y 30
    char title[] = "ALARM SETT.";
    char text[] = "hh:mm";
    //set the font
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_GRAY);
    Graphics_setFont(gc, &g_sFontCm18b);
    Graphics_drawString(gc, (int8_t*) text, sizeof(text), TEXT_POSITION_X, TEXT_POSITION_Y, OPAQUE_TEXT);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
    drawTitle(gc, title);
}


/* TIME SETTINGS VIEW */
void timeSettView(Graphics_Context *gc, volatile uint8_t *menuA){
    RTC_C_Calendar settedTime = currentTime;
    uint8_t cursor = 1;
    uint8_t updateCursor = 1;
    uint8_t up = 0;
    uint8_t down = 0;
    uint8_t updateDate = 1;
    initTimeSettView(gc);
    drawTimeMenu(gc);

    uint8_t hours = RTC_C_convertBCDToBinary(settedTime.hours);
    uint8_t minutes = RTC_C_convertBCDToBinary(settedTime.minutes);
    uint8_t dayOfWeek = RTC_C_convertBCDToBinary(settedTime.dayOfWeek);
    uint8_t dayOfmonth = RTC_C_convertBCDToBinary(settedTime.dayOfmonth);
    uint8_t month = RTC_C_convertBCDToBinary(settedTime.month);
    uint16_t year = RTC_C_convertBCDToBinary(settedTime.year);
    joystick joy;
    startADCconversions();
    while(!buttonsPressed.jb){
        joy = getJoyValue();


        if(!(joy.joyYvalue<50 && joy.joyYvalue>-50)){
            int i;
            switch(cursor){
                case 1:
                    if(joy.joyYvalue>0){
                        hours = (hours + 1)%24;
                    }else{
                        if(hours-1 > 0){
                            hours = hours - 1;
                        }else{
                            hours = 23;
                        }
                    }
                    break;
                case 2:
                    if(joy.joyYvalue>0){
                        minutes = (minutes + 1)%60;
                    }else{
                        if(minutes-1 > 0){
                            minutes = minutes - 1;
                        }else{
                            minutes = 59;
                        }
                    }
                    break;
                case 3:
                    updateDate = 1;
                    if(joy.joyYvalue>0){
                        dayOfWeek = (dayOfWeek + 1)%7;
                    }else{
                        if(dayOfWeek-1 > 0){
                            dayOfWeek = dayOfWeek - 1;
                        }else{
                            dayOfWeek = 6;
                        }
                    }
                    break;
                case 4:
                    updateDate = 1;
                    if(joy.joyYvalue>0){
                        if(month == 2){
                            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                                dayOfmonth = (dayOfmonth + 1)%30;
                            }else{
                                dayOfmonth = (dayOfmonth + 1)%29;
                            }
                        }else{
                            if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
                                dayOfmonth = (dayOfmonth + 1)%32;
                            }else{
                                dayOfmonth = (dayOfmonth + 1)%31;
                            }
                        }
                        if(dayOfmonth == 0){
                            dayOfmonth = 1;
                        }
                    }else{
                        if(dayOfmonth-1 > 0){
                            dayOfmonth = dayOfmonth - 1;
                        }else{
                            if(month == 2){
                                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                                    dayOfmonth = 29;
                                }else{
                                    dayOfmonth = 28;
                                }
                            }else{
                                dayOfmonth = 31;
                            }
                        }
                    }
                    break;
                case 5:
                    updateDate = 1;
                    if(joy.joyYvalue>0){
                        month = (month + 1)%13;
                        if(month == 0){
                            month = 1;
                        }
                    }else{
                        if(month-1 > 1){
                            month = month - 1;
                        }else{
                            month = 12;
                        }
                    }
                    break;
                case 6:
                    updateDate = 1;
                    if(joy.joyYvalue>0){
                        year++;
                    }else{
                        year--;
                    }
                    break;
            }
            settedTime.hours = RTC_C_convertBinaryToBCD(hours);
            settedTime.minutes = RTC_C_convertBinaryToBCD(minutes);
            settedTime.dayOfWeek = RTC_C_convertBinaryToBCD(dayOfWeek);
            settedTime.dayOfmonth = RTC_C_convertBinaryToBCD(dayOfmonth);
            settedTime.month = RTC_C_convertBinaryToBCD(month);
            settedTime.year = RTC_C_convertBinaryToBCD(year);
            if(!(joy.joyYvalue<100 && joy.joyYvalue>-100)){
               for(i=0; i<10000;i++);   //small delay, faster incrementation
            }else{
               for(i=0; i<100000;i++);   //big delay, slower incrementation
            }
        }

        drawTime(gc, settedTime);
        if(updateDate){
            drawDate(gc, settedTime);
            updateDate = 0;
        }
        getCursorPosition(6, &cursor, &updateCursor, &up, &down, joy, AXIS_X);
        if(updateCursor == 1){
            drawCursor(gc, cursor, *menuA);
            updateCursor = 0;
        }
    }
    RTC_C_initCalendar(&settedTime, RTC_C_FORMAT_BCD);
    *menuA = 0;
    buttonsPressed.jb = 0;
    stopADCconversions();
}

// DRAW TIME SETTINGS MENU
void drawTimeMenu(Graphics_Context *gc){
    #define TEXT_POSITION_X 35
    #define TEXT_POSITION_Y 30
    char title[] = "TIME SETT.";
    char text[] = "hh:mm";
    //set the font
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_GRAY);
    Graphics_setFont(gc, &g_sFontCm18b);
    Graphics_drawString(gc, (int8_t*) text, sizeof(text), TEXT_POSITION_X, TEXT_POSITION_Y, OPAQUE_TEXT);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
    drawTitle(gc, title);
}

/* INIT TIME SETTINGS VIEW */
void initTimeSettView(Graphics_Context *gc){
    resetButtonsState();
    updateTime = 1;
    Graphics_Rectangle fillRectangle;
    fillRectangle.xMin = 0;
    fillRectangle.xMax = 127;
    fillRectangle.yMin = 0;
    fillRectangle.yMax = 127;
    //color the entire frame of black
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_fillRectangle(gc, &fillRectangle);
    //set background black and the text/obj white
    Graphics_setBackgroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
}

/* SETTINGS VIEW*/
void settingsView(Graphics_Context *gc,  volatile uint8_t *menuA) {
    uint8_t cursor = 1;
    uint8_t updateCursor = 1;
    uint8_t up = 0;
    uint8_t down = 0;
    initSettingsView(gc);
    char title[20] = "SETTINGS";
    drawTitle(gc, title);
    drawMenu(gc);
    drawCursor(gc, cursor, *menuA);

    joystick joy;
    startADCconversions();
    while(!buttonsPressed.jb){
        /* CHANGE THE CURSOR POSITION */
        joy = getJoyValue();
        getCursorPosition(2, &cursor, &updateCursor, &up, &down, joy, AXIS_Y);
        if(updateCursor == 1){
            drawCursor(gc, cursor, *menuA);
            updateCursor = 0;
        }
        if(buttonsPressed.b2){
            *menuA = cursor+1;
            buttonsPressed.b2 = 0;
            return;
        }
    }
    buttonsPressed.jb = 0;      //remember to reset the button state
    *menuA = 0;
    stopADCconversions();
}


// UPDATE CURSOR
void getCursorPosition(uint8_t max, uint8_t *cursor,uint8_t *updateCursor, uint8_t *up, uint8_t *down, joystick joy, uint8_t axis){
    int axisValue = 0;
    if(axis == 0){
        axisValue = -joy.joyXvalue;
    }else{
        axisValue = joy.joyYvalue;
    }

    if(axisValue>80){
            *up = 1;
        }
        if(axisValue<-80){
            *down = 1;
        }
        if (axisValue<10 && axisValue>-10){
            *up = 0;
            *down = 0;
        }
        if(*up == 1 && *down == 0){
            if(*cursor-1>0){
                *cursor = *cursor - 1;
            }
            *updateCursor = 1;
            *down = 1;
        }
        if(*down == 1 && *up == 0){
            if(*cursor+1 < max+1){
                *cursor = *cursor + 1;
            }
            *updateCursor = 1;
            *up = 1;
        }
}

// DRAW CURSOR
void drawCursor(Graphics_Context *gc, uint8_t position, uint8_t menu){
    Graphics_Rectangle clearCursorSettings;
    clearCursorSettings.xMin = 0;
    clearCursorSettings.xMax = 15;
    clearCursorSettings.yMin = 22;
    clearCursorSettings.yMax = 127;
    Graphics_Rectangle clearCursorTime;
    clearCursorTime.xMin = 0;
    clearCursorTime.xMax = 107;
    clearCursorTime.yMin = 79;
    clearCursorTime.yMax = 118;


    switch (menu) {
        case 1:
            //draw the icon
            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(gc, &clearCursorSettings);
            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
            Graphics_drawImage(gc, &CURSOR_R1BPP_UNCOMP, 3, 5+position*17);
            break;
        case 2:
            //draw the icon
            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(gc, &clearCursorTime);
            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
            int x = 0;
            int y = 0;
            int direction = 0;  // if 1->up, if 0->down
            switch(position){
                case 1: x = 40; y = 83; direction = 1; break;
                case 2: x = 80; y = 83; direction = 1; break;
                case 3: x = 4; y = 105; direction = 0; break;
                case 4: x = 23; y = 105; direction = 0; break;
                case 5: x = 45; y = 105; direction = 0; break;
                case 6: x = 72; y = 105; direction = 0; break;
            }
            if(direction){
                Graphics_drawImage(gc, &CURSOR_UP1BPP_UNCOMP, x, y);
            }else{
                Graphics_drawImage(gc, &CURSOR_DOWN1BPP_UNCOMP, x, y);
            }
            break;
            case 3:
                //draw the icon
                Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
                Graphics_fillRectangle(gc, &clearCursorTime);
                Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
                switch(position){
                    case 1: x = 40; y = 83; break;
                    case 2: x = 80; y = 83; break;
                }
                Graphics_drawImage(gc, &CURSOR_UP1BPP_UNCOMP, x, y);
                break;
    }
}

// INIT SETTINGS VIEW
void initSettingsView(Graphics_Context *gc) {
    resetButtonsState();
    Graphics_Rectangle fillRectangle;
    fillRectangle.xMin = 0;
    fillRectangle.xMax = 127;
    fillRectangle.yMin = 0;
    fillRectangle.yMax = 127;
    //color the entire frame of black
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_fillRectangle(gc, &fillRectangle);
    //set background black and the text/obj white
    Graphics_setBackgroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
}

//DRAW TITLE
void drawTitle(Graphics_Context *gc, char t[20]){
    Graphics_setFont(gc, &g_sFontCm16b);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLUE);
    Graphics_drawString(gc, (int8_t*) t, 20, 0, 0,OPAQUE_TEXT);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
}

//DRAW MENU
void drawMenu(Graphics_Context *gc){
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
    Graphics_setFont(gc, &g_sFontCm16b);
    char menu1[] = "TIME";
    char menu2[] = "ALARM";
    Graphics_drawString(gc, (int8_t*) menu1, sizeof(menu1), 20, 5+17,OPAQUE_TEXT);
    Graphics_drawString(gc, (int8_t*) menu2, sizeof(menu2), 20, 5+17*2,OPAQUE_TEXT);
}


/* CLOCK VIEW */
timerNumber onesTimer;

void clockView(Graphics_Context *gc, volatile uint8_t *menuA, volatile uint8_t *alarmOn) {
    initClockView(gc, *alarmOn);
    onesTimer = generate_rate(250, &IRQdrawClock);
    while(!buttonsPressed.jb) {  // exit this loop when the joystick button are pressed and enter the menu viewed
        if(buttonsPressed.b1){
            *alarmOn = (*alarmOn+1)%2;
            drawAlarm(gc, *alarmOn);
            if(*alarmOn == 1){
                RTC_C_enableInterrupt(RTC_C_CLOCK_ALARM_INTERRUPT);
            }
            if(*alarmOn == 0){
                RTC_C_disableInterrupt(RTC_C_CLOCK_ALARM_INTERRUPT);
            }

            buttonsPressed.b1 = 0;
        }
        if(updateClockImage){
            drawClock(gc);
        }
        if(updateTime){
            drawTime(gc, currentTime);
        }
        if(updateDate){
            drawDate(gc,currentTime);
        }
        if(alarmFired == 1){
            disable_timer(onesTimer);
            return;
        }

    }
    disable_timer(onesTimer);
    buttonsPressed.jb = 0;      // remember to reset the button state
    *menuA = 1;
}

void drawAlarm(Graphics_Context *gc, uint8_t alarmOn){
    if(alarmOn){
        Graphics_drawImage(gc, &ALARM_ON8BPP_UNCOMP, 0, 0);
        char t[10];
        sprintf(t," %02d:%02d", RTC_C_convertBCDToBinary(alarmTime.hours), RTC_C_convertBCDToBinary(alarmTime.minutes));
        Graphics_setFont(gc, &g_sFontCm14);
        Graphics_drawString(gc, (int8_t*) t, sizeof(t), 20, 3, OPAQUE_TEXT);
    }else{
        Graphics_Rectangle fillRectangle;
        fillRectangle.xMin = 20;
        fillRectangle.xMax = 64;
        fillRectangle.yMin = 0;
        fillRectangle.yMax = 20;
        Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(gc, &fillRectangle);
        Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
        Graphics_drawImage(gc, &ALARM_OFF8BPP_UNCOMP, 0, 0);
    }
}

/* 1s interrupt */
void IRQdrawClock(void){
    clockImage = (clockImage+1)%4;
    updateClockImage = 1;
}

void drawClock(Graphics_Context *gc){
    switch(clockImage){
        case 0: Graphics_drawImage(gc, &CLOCK_18BPP_UNCOMP, 97, 0); break;
        case 1: Graphics_drawImage(gc, &CLOCK_28BPP_UNCOMP, 97, 0); break;
        case 2: Graphics_drawImage(gc, &CLOCK_38BPP_UNCOMP, 97, 0); break;
        case 3: Graphics_drawImage(gc, &CLOCK_48BPP_UNCOMP, 97, 0); break;
    }
    updateClockImage = 0;

}

/* CLOCK VIEW FUNCTIONS */
void initClockView(Graphics_Context *gc, uint8_t alarmOn) {
    resetButtonsState();
    updateDate = 1;
    updateTime = 1;
    updateClockImage = 1;
    Graphics_Rectangle fillRectangle;
    fillRectangle.xMin = 0;
    fillRectangle.xMax = 127;
    fillRectangle.yMin = 0;
    fillRectangle.yMax = 127;
    //color the entire frame of black
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_fillRectangle(gc, &fillRectangle);
    //set background black and the text/obj white
    Graphics_setBackgroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
    drawAlarm(gc, alarmOn);
    currentTime = RTC_C_getCalendarTime();
}

//DRAW TIME ON THE DIPLAY
void drawTime(Graphics_Context *gc, RTC_C_Calendar t) {
    #define TIME_POSITION_X 30
    #define TIME_POSITION_Y 47
    //set the font
    Graphics_setFont(gc, &g_sFontCm34b);

    char time[10];
    sprintf(time, "%02d:%02d",RTC_C_convertBCDToBinary( t.hours),RTC_C_convertBCDToBinary( t.minutes));
    Graphics_drawString(gc, (int8_t*) time, sizeof(time), TIME_POSITION_X, TIME_POSITION_Y, OPAQUE_TEXT);  // (the background will be drown)
    updateTime = 0;     // time updated
}

//DRAW DATE ON THE DISPLAY
void drawDate(Graphics_Context *gc, RTC_C_Calendar time) {
    #define DATE_POSITION_X 0
    #define DATE_POSITION_Y 120

    //set the font
    Graphics_setFont(gc, &g_sFontFixed6x8);

    char day[10];
    char numb[10];
    char month[10];
    char year[10];
    switch(time.dayOfWeek){
        case 0: strcpy(day,"Sun"); break;
        case 1: strcpy(day,"Mon"); break;
        case 2: strcpy(day,"Tue"); break;
        case 3: strcpy(day,"Wed"); break;
        case 4: strcpy(day,"Thu"); break;
        case 5: strcpy(day,"Fri"); break;
        case 6: strcpy(day,"Sat"); break;
    }
    sprintf(numb,"%02d",RTC_C_convertBCDToBinary(time.dayOfmonth));

    switch(RTC_C_convertBCDToBinary(time.month)){
        case 1: strcpy(month,"Jan "); break;
        case 2: strcpy(month,"Feb "); break;
        case 3: strcpy(month,"Mar "); break;
        case 4: strcpy(month,"Apr "); break;
        case 5: strcpy(month,"May "); break;
        case 6: strcpy(month,"June"); break;
        case 7: strcpy(month,"July"); break;
        case 8: strcpy(month,"Aug "); break;
        case 9: strcpy(month,"Sept"); break;
        case 10: strcpy(month,"Oct "); break;
        case 11: strcpy(month,"Nov "); break;
        case 12: strcpy(month,"Dec "); break;
    }

    sprintf(year, "%d", RTC_C_convertBCDToBinary(time.year));

    //sprintf(date, "%s %s %3s %s", day, numb, month, year);
   // Graphics_drawString(gc, (int8_t*) date, sizeof(date), DATE_POSITION_X, DATE_POSITION_Y, OPAQUE_TEXT);  // (the background will be drown)

    Graphics_drawString(gc, (int8_t*) day, sizeof(day), DATE_POSITION_X, DATE_POSITION_Y, OPAQUE_TEXT);
    Graphics_drawString(gc, (int8_t*) numb, sizeof(numb), DATE_POSITION_X+22, DATE_POSITION_Y, OPAQUE_TEXT);
    Graphics_drawString(gc, (int8_t*) month, sizeof(month), DATE_POSITION_X+22+17, DATE_POSITION_Y, OPAQUE_TEXT);
    Graphics_drawString(gc, (int8_t*) year, sizeof(year), DATE_POSITION_X+22+17+27, DATE_POSITION_Y, OPAQUE_TEXT);
    updateDate = 0;
}

/* DRAW SECONDS CLOCK IMMAGE */
void drawSeconds(Graphics_Context *gc) {
}



/* RTC IRQ */
void RTC_C_IRQHandler(void) {
    uint32_t status;
    status = MAP_RTC_C_getEnabledInterruptStatus();
    RTC_C_clearInterruptFlag(status);

    if (status & RTC_C_TIME_EVENT_INTERRUPT){
        /*
        GPIO_toggleOutputOnPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);
        int i;
        for(i=0; i<1000;i++);   //big delay, slower incrementation
        GPIO_toggleOutputOnPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);
        */

        updateTime = 1;       //display need a time update (updated every minute)
        currentTime = RTC_C_getCalendarTime();
        if(currentTime.hours == 0 && currentTime.minutes == 0) {    // check if the date need an update
            updateDate = 1;
        }

    }
    if (status & RTC_C_CLOCK_ALARM_INTERRUPT) {
        alarmFired = 1;
    }
}



