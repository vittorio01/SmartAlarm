#include "clock.h"

void testJoy(Graphics_Context *gc) { //only a test
    joystick adcJoy;    //joystic values

    adcJoy = getJoyValue();

    char joy[20];
    sprintf(joy, "x: %3d   y:%3d", (int) adcJoy.joyXvalue, (int) adcJoy.joyYvalue);
    Graphics_drawString(gc, (int8_t*) joy, sizeof(joy), 10, 20,OPAQUE_TEXT);
}

/* TIME SETTINGS VIEW */
void timeSettView(Graphics_Context *gc, volatile uint8_t *menuA){
    RTC_C_Calendar settedTime = currentTime;
    uint8_t cursor = 1;
    uint8_t updateCursor = 1;
    uint8_t up = 0;
    uint8_t down = 0;
    initTimeSettView(gc);
    drawTimeMenu(gc);

    uint8_t hours = RTC_C_convertBCDToBinary(settedTime.hours);
    uint8_t minutes = RTC_C_convertBCDToBinary(settedTime.minutes);
    joystick joy;
    while(!buttonsPressed.jb){
        joy = getJoyValue();
        drawTime(gc, settedTime);

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
            }
            settedTime.hours = RTC_C_convertBinaryToBCD(hours);
            settedTime.minutes = RTC_C_convertBinaryToBCD(minutes);
            if(!(joy.joyYvalue<100 && joy.joyYvalue>-100)){
               for(i=0; i<10000;i++);   //small delay, faster incrementation
            }else{
               for(i=0; i<100000;i++);   //big delay, slower incrementation
            }
        }

        getCursorPosition(2, &cursor, &updateCursor, &up, &down, joy, AXIS_X);
        if(updateCursor == 1){
            drawCursor(gc, cursor, *menuA);
            updateCursor = 0;
        }
    }
    RTC_C_initCalendar(&settedTime, RTC_C_FORMAT_BCD);
    *menuA = 0;
    buttonsPressed.jb = 0;
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
    updateDate = 1;
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
    while(!buttonsPressed.jb){
        /* CHANGE THE CURSOR POSITION */
        joy = getJoyValue();
        getCursorPosition(4, &cursor, &updateCursor, &up, &down, joy, AXIS_Y);
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
}


// UPDATE CIRSOR
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
    clearCursorTime.xMin = 27;
    clearCursorTime.xMax = 107;
    clearCursorTime.yMin = 79;
    clearCursorTime.yMax = 111;
    char cursorSettings[] = "X";
    char cursorTime[] = "i";

    switch (menu) {
        case 1:
            //draw the icon
            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(gc, &clearCursorSettings);
            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
            Graphics_drawString(gc, (int8_t*) cursorSettings, sizeof(cursorSettings), 0, 5+position*17,OPAQUE_TEXT);
            break;
        case 2:
            //draw the icon
            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(gc, &clearCursorTime);
            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
            Graphics_setFont(gc, &g_sFontCm32b);
            if(position == 1){
                Graphics_drawString(gc, (int8_t*) cursorTime, sizeof(cursorTime), 37, 79,OPAQUE_TEXT);
            }else{
                Graphics_drawString(gc, (int8_t*) cursorTime, sizeof(cursorTime), 77, 79,OPAQUE_TEXT);
            }
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
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLUE);
    Graphics_drawString(gc, (int8_t*) t, 20, 0, 0,OPAQUE_TEXT);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
}

//DRAW MENU
void drawMenu(Graphics_Context *gc){
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
    Graphics_setFont(gc, &g_sFontCm16b);
    char menu1[] = "TIME";
    char menu2[] = "DATE";
    char menu3[] = "ALARM";
    char menu4[] = "ALARM";
    Graphics_drawString(gc, (int8_t*) menu1, sizeof(menu1), 20, 5+17,OPAQUE_TEXT);
    Graphics_drawString(gc, (int8_t*) menu2, sizeof(menu2), 20, 5+17*2,OPAQUE_TEXT);
    Graphics_drawString(gc, (int8_t*) menu3, sizeof(menu3), 20, 5+17*3,OPAQUE_TEXT);
    Graphics_drawString(gc, (int8_t*) menu4, sizeof(menu4), 20, 5+17*4,OPAQUE_TEXT);
}


/* CLOCK VIEW */
void clockView(Graphics_Context *gc, volatile uint8_t *menuA) {
    initClockView(gc);

    while(!buttonsPressed.jb) {  // exit this loop when the joystick button are pressed and enter the menu viewd
        if(updateTime){
            drawTime(gc, currentTime);
        }
        if(updateDate){
            drawDate(gc);
        }
    }
    buttonsPressed.jb = 0;      //remeber to reset the button state
    *menuA = 1;

}


/* CLOCK VIEW FUNCTIONS */
void initClockView(Graphics_Context *gc) {
    resetButtonsState();
    updateDate = 1;
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
void drawDate(Graphics_Context *gc) {
    #define DATE_POSITION_X 0
    #define DATE_POSITION_Y 111

    //set the font
    Graphics_setFont(gc, &g_sFontCm16b);

    char date[20];
    char day[10];
    char numb[10];
    char month[10];
    switch(currentTime.dayOfWeek){
        case 0: strcpy(day,"Sun"); break;
        case 1: strcpy(day,"Mon"); break;
        case 2: strcpy(day,"Tue"); break;
        case 3: strcpy(day,"Wed"); break;
        case 4: strcpy(day,"Thu"); break;
        case 5: strcpy(day,"Fri"); break;
        case 6: strcpy(day,"Sat"); break;
    }
    sprintf(numb,"%d",RTC_C_convertBCDToBinary(currentTime.dayOfmonth));

    switch(RTC_C_convertBCDToBinary(currentTime.month)){
        case 1: strcpy(month,"Jan"); break;
        case 2: strcpy(month,"Feb"); break;
        case 3: strcpy(month,"Mar"); break;
        case 4: strcpy(month,"Apr"); break;
        case 5: strcpy(month,"May"); break;
        case 6: strcpy(month,"June"); break;
        case 7: strcpy(month,"July"); break;
        case 8: strcpy(month,"Aug"); break;
        case 9: strcpy(month,"Sept"); break;
        case 10: strcpy(month,"Oct"); break;
        case 11: strcpy(month,"Nov"); break;
        case 12: strcpy(month,"Dec"); break;
    }

    sprintf(date, "%s %s %s", day, numb, month);
    Graphics_drawString(gc, (int8_t*) date, sizeof(date), DATE_POSITION_X, DATE_POSITION_Y, OPAQUE_TEXT);  // (the background will be drown)

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
        GPIO_toggleOutputOnPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);
        updateTime = 1;       //display need a time update (updated every minute)
        currentTime = RTC_C_getCalendarTime();
        if(currentTime.hours == 0 && currentTime.minutes == 0) {    // check if the date need an update
            updateDate = 1;
        }

    }
}



