#include "clock.h"

 static volatile RTC_C_Calendar currentTime;


void testJoy(Graphics_Context *gc) { //only a test
    joystick adcJoy;    //joystic values

    adcJoy = getJoyValue();

    char joy[20];
    sprintf(joy, "x: %3d   y:%3d", (int) adcJoy.joyXvalue, (int) adcJoy.joyYvalue);
    Graphics_drawString(gc, (int8_t*) joy, sizeof(joy), 10, 20,OPAQUE_TEXT);
}


void initClockView(Graphics_Context *gc) {
    Graphics_Rectangle fillRectangle;
    //color the entire frame of black
    Graphics_setForegroundColor(gc, 0x00000);
    Graphics_fillRectangle(gc, &fillRectangle);
    //set background black and the text/obj white
    Graphics_setBackgroundColor(gc, 0x0);
    Graphics_setForegroundColor(gc, 0xFFFFFF);
    //set the font
    //Graphics_setFont(gc, &g_sFontCm16b);
}


void drawTime(Graphics_Context *gc) {
    char time[10];
    sprintf(time, "%02d:%02d",currentTime.hours, currentTime.minutes);
    Graphics_drawString(gc, (int8_t*) time, sizeof(time), 49, 60, OPAQUE_TEXT);  // (the background will be drown)

}

void drawDate(Graphics_Context *gc) {
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
    sprintf(numb,"%d",currentTime.dayOfmonth);

    switch(currentTime.dayOfWeek){
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
    Graphics_drawString(gc, (int8_t*) date, sizeof(date), 0, 122, OPAQUE_TEXT);  // (the background will be drown)

}




/* RTC IRQ */
void RTC_C_IRQHandler(void) {
    uint32_t status;
    status = MAP_RTC_C_getEnabledInterruptStatus();
    MAP_RTC_C_clearInterruptFlag(status);

    if (status & RTC_C_TIME_EVENT_INTERRUPT){
        currentTime = MAP_RTC_C_getCalendarTime();

    }
}
