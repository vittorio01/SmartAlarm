#include "treasure_hunt.h"


int x0=0, x1=0, y0=0, y1=0;

state treasure_hunt_start(Graphics_Context* gc) {
    inactivity_timer=NONE;
    clearscreen2(gc);
    char* title[] = TITLE_TEXT;
    printTitleMessage2(title,TITLE_DIMENSION,gc);
    generate_wait(TITLE_SHOW_TIME);

    char* gameDescription[]=GAME_DESCRIPTION_TEXT1;
    printMessage2 (gameDescription,GAME_DESCRIPTION_TEXT1_DIMENSION,gc);
    int showTime=GAME_DESCRIPTION_SHOW_TIME;
    while (showTime>0) {
        if (buttonsPressed.b1) {
            break;
        }
        generate_wait(BUTTON_POLLING_DELAY);
        showTime=showTime-BUTTON_POLLING_DELAY;
    }

    treasure treasure;

    clearscreen2(gc);
    startADCconversions();
    resetInactivityTimer2();
    joystick position;
    time_t t;
    srand((unsigned) time(&t));

    int i;
    for(i=0;i<=STAGE_GENERATION_NUMBER;i++){
        int color = GRAPHICS_COLOR_RED;
        newTreasure(&treasure);
        while(color != GRAPHICS_COLOR_GREEN){

            position=getJoyValue();
            color = checkPosition(position,treasure);
            printRectangle(position, gc, color);
            if (getInactivityTimerStatus2()) {
                clearScreen(gc);
                return USER_INACTIVE;
            }
        }
        generate_wait(200);
        Graphics_Rectangle winRectangle;
        winRectangle.xMin = position.joyXvalue + 65 - 8;
        winRectangle.xMax = position.joyXvalue + 65 + 8;
        winRectangle.yMin = 65 - position.joyYvalue - 8;
        winRectangle.yMax = 65 - position.joyYvalue + 8;
        Graphics_setForegroundColor(gc, GRAPHICS_COLOR_GREEN);
        Graphics_fillRectangle(gc, &winRectangle);
        Graphics_drawImage(gc,&v1BPP_UNCOMP2,55,80);
        generate_wait(1000);
        clearscreen2(gc);


    }
    char* endMessage[]=END_MESSAGE_TEXT;
    printTitleMessage2(endMessage,END_MESSAGE_DIMENSION,gc);
    generate_wait(2000);
    clearscreen2(gc);
    stopADCconversions();
    stopInactivityTimer2();
    return TASK_COMPLETED;
}

void inactivityHandler2() {
    inactivity_status=true;
}

void resetInactivityTimer2() {
    inactivity_status=false;
    disable_timer(inactivity_timer);
    inactivity_timer=NONE;
    inactivity_timer=generate_delay(INACTIVITY_TIME,&inactivityHandler2);
}
bool getInactivityTimerStatus2() {
    return inactivity_status;
}

void stopInactivityTimer2() {
    disable_timer(inactivity_timer);
    inactivity_timer=NONE;
}

void printTitleMessage2(char* message[],int lines,Graphics_Context* gc) {
    if (lines==0) return;
    clearscreen2(gc);
    Graphics_setFont(gc, TITLE_FONT);
    int title_height=Graphics_getStringHeight(gc);

    int i,size;
    int pos_y;
    if (lines>1) {
        pos_y=(((DISPLAY_SIZE_Y-1)/lines)-((lines/2)*(title_height+(TITLE_SPACING))));
    } else {
        pos_y=(DISPLAY_SIZE_Y-1)/2-(title_height/2);
    }
    int pos_x=0;
    int width;
    for (i=0;i<lines;i++) {
        for(size=0;message[i][size];size++);
        width=Graphics_getStringWidth(gc,(int8_t*) message[i],size);
        pos_x=((DISPLAY_SIZE_X-1)-width)/2;
        Graphics_drawString(gc, (int8_t*) message[i],size,pos_x, pos_y,false);
        pos_y=pos_y+(TITLE_SPACING)+title_height;
    }
}

void clearscreen2(Graphics_Context* gc) {
    Graphics_Rectangle fillRectangle;
    fillRectangle.xMin = 0;
    fillRectangle.xMax = DISPLAY_SIZE_X-1;
    fillRectangle.yMin = 0;
    fillRectangle.yMax = DISPLAY_SIZE_Y-1;
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_fillRectangle(gc, &fillRectangle);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
}

void printMessage2(char* message[],int lines,Graphics_Context* gc) {
    clearscreen2(gc);
    int pos_y=MESSAGE_MARGIN_Y;
    int i,size;
    Graphics_setFont(gc, MESSAGE_FONT);
    int description_font_height=Graphics_getStringHeight(gc);
    for (i=0;i<(lines);i++) {
        for (size=0;message[i][size]!='\0';size++);
        Graphics_drawString(gc, (int8_t*) message[i],size,MESSAGE_MARGIN_X, pos_y,false);
        pos_y=pos_y+MESSAGE_SPACING+description_font_height;
    }
}

void newTreasure(treasure* treasure){

    treasure->x = (rand() % (JOYPAD_MAX_X_VALUE));
    treasure->y = (rand() % (JOYPAD_MAX_Y_VALUE));
    /*treasure->x = 10;
    treasure->y = 10;*/
}

void printRectangle(joystick position, Graphics_Context* gc, int color){
    int x2,x3,y2,y3;
    x2=(position.joyXvalue) + 65;
    x3=(position.joyXvalue)+ 65 + 2;
    y2=130-(position.joyYvalue) - 65;
    y3=130-(position.joyYvalue) - 65 + 2;
    Graphics_Rectangle blank={x0,y0,x1,y1};
    if(x0!=x2 || y0!=y2){
        Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(gc, &blank);
    }
    Graphics_setForegroundColor(gc, color);
    Graphics_Rectangle pointer={x2,y2,x3,y3};
    Graphics_fillRectangle(gc, &pointer);
    x0=x2;
    x1=x3;
    y0=y2;
    y1=y3;

}

int checkPosition(joystick position, treasure treasure){
    int check;
    if(position.joyXvalue+ 65<(treasure.x+10)&&position.joyXvalue+ 65>(treasure.x-10)&&130-position.joyYvalue-65<(treasure.y+10)&&130-position.joyYvalue-65>(treasure.y-10))
        check = GRAPHICS_COLOR_GREEN;
    else if(position.joyXvalue+ 65<(treasure.x+35)&&position.joyXvalue+ 65>(treasure.x-35)&&130-position.joyYvalue-65<(treasure.y+35)&&130-position.joyYvalue-65>(treasure.y-35))
        check = GRAPHICS_COLOR_YELLOW;
    else
        check = GRAPHICS_COLOR_RED;
    return check;
}


