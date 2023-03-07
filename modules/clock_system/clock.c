#include "clock.h"

void testJoy(Graphics_Context *gc) { //only a test
    joystick adcJoy;    //joystic values

    adcJoy = getJoyValue();

    char joy[20];
    sprintf(joy, "x: %3d   y:%3d", (int) adcJoy.joyXvalue, (int) adcJoy.joyYvalue);
    Graphics_drawString(gc, (int8_t*) joy, sizeof(joy), 10, 20,OPAQUE_TEXT);
}



/* SETTINGS VIEW*/
void settingsView(Graphics_Context *gc,  volatile uint8_t *menuA) {
    uint8_t cursor = 1;
    uint8_t updateCursor = 0;
    uint8_t up = 0;
    uint8_t down = 0;
    initSettingsView(gc);
    char title[20] = "SETTINGS";
    drawTitle(gc, title);
    drawMenu(gc);
    drawCursor(gc, cursor, *menuA);

    joystick joy;
    while(!buttonsPressed.jb){

        joy = getJoyValue();
        if(joy.joyYvalue>80){
            up = 1;
        }

        if(joy.joyYvalue<-80){
            down = 1;
        }

        if (joy.joyYvalue<10 && joy.joyYvalue>-10){
            up = 0;
            down = 0;
        }

        if(up == 1 && down == 0){
            if(cursor-1>0){
                cursor--;
            }
            updateCursor = 1;
            down = 1;
        }

        if(down == 1 && up == 0){
            if(cursor+1 < 5){
                cursor++;
            }
            updateCursor = 1;
            up = 1;
        }

        if(updateCursor == 1){
            drawCursor(gc, cursor, *menuA);
            updateCursor = 0;
        }
    }
    buttonsPressed.jb = 0;      //remember to reset the button state
    *menuA = 0;
}

// DRAW CURSOR
void drawCursor(Graphics_Context *gc, uint8_t position, uint8_t menu){
    Graphics_Rectangle clearCursor;
    clearCursor.xMin = 0;
    clearCursor.xMax = 15;
    clearCursor.yMin = 22;
    clearCursor.yMax = 127;
    char cursor[] = "X";
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_fillRectangle(gc, &clearCursor);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
    switch (menu) {
        case 1:
            Graphics_drawString(gc, (int8_t*) cursor, sizeof(cursor), 0, 5+position*17,OPAQUE_TEXT);
            break;

    }
}

// INIT SETTINGS VIEW
void initSettingsView(Graphics_Context *gc) {
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
            drawTime(gc);
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

//DRAW TIME ON THE DIPLAY
void drawTime(Graphics_Context *gc) {
    currentTime = MAP_RTC_C_getCalendarTime();
    #define TIME_POSITION_X 27
    #define TIME_POSITION_Y 47
    //set the font
    Graphics_setFont(gc, &g_sFontCm34b);

    char time[10];
    sprintf(time, "%02d:%02d",RTC_C_convertBCDToBinary( currentTime.hours),RTC_C_convertBCDToBinary( currentTime.minutes));
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
    MAP_RTC_C_clearInterruptFlag(status);

    if (status & RTC_C_TIME_EVENT_INTERRUPT){
        GPIO_toggleOutputOnPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);
        updateTime = 1;       //display need a time update (updated every minute)
        currentTime = MAP_RTC_C_getCalendarTime();
        if(currentTime.hours == 0 && currentTime.minutes == 0) {    // check if the date need an update
            updateDate = 1;
        }

    }
}



