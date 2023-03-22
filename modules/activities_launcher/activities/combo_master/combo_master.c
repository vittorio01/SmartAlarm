#include "combo_master.h"

const tImage* index[MOVEMENTS_NUMBER]={&down_arrow1BPP_UNCOMP,&up_arrow1BPP_UNCOMP,&left_arrow1BPP_UNCOMP,&right_arrow1BPP_UNCOMP,&a1BPP_UNCOMP,&b1BPP_UNCOMP};

state combo_master_start(Graphics_Context* gc) {
    inactivity_timer=NONE;
    clearScreen(gc);
    char* title[] = TITLE_TEXT;
    printTitleMessage(title,TITLE_DIMENSION,gc);
    generate_wait(TITLE_SHOW_TIME);

    char* gameDescription[]=GAME_DESCRIPTION_TEXT1;
    printMessage (gameDescription,GAME_DESCRIPTION_TEXT1_DIMENSION,gc);
    int showTime=GAME_DESCRIPTION_SHOW_TIME;
    while (showTime>0) {
        if (buttonsPressed.b1) {
            break;
        }
        generate_wait(BUTTON_POLLING_DELAY);
        showTime=showTime-BUTTON_POLLING_DELAY;
    }
    clearScreen(gc);
    resetButtonsState();
    startADCconversions();
    tImage* generation[ACTION_GENERATION_NUMBER];
    time_t t;
    srand((unsigned) time(&t));
    int pos_x=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
    int pos_y=(DISPLAY_SIZE_Y/2)-(IMAGES_WIDTH/2)-(IMAGES_BOTTOM_MARGIN/2);
    int pos_y2=pos_y+IMAGES_BOTTOM_MARGIN;
    int pos_x2=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
    Graphics_Rectangle clearLine;
    clearLine.xMin = pos_x2;
    clearLine.xMax = pos_x2+(IMAGES_WIDTH*ACTION_GENERATION_NUMBER);
    clearLine.yMin = pos_y2;
    clearLine.yMax = pos_y2+IMAGES_WIDTH;
    int i,j;
    resetInactivityTimer();
    for (i=0;i<STAGE_GENERATION_NUMBER;i++) {
        for (j=0;j<ACTION_GENERATION_NUMBER;j++) {
            generation[j]=index[rand() % MOVEMENTS_NUMBER];
            Graphics_drawImage(gc, generation[j], pos_x, pos_y);
            pos_x=pos_x+IMAGES_WIDTH;
        }
        j=0;
        while(j<ACTION_GENERATION_NUMBER) {
            if (getInactivityTimerStatus()) {
                clearScreen(gc);
                return USER_INACTIVE;
            }
            switch(getJoyMovement()) {
            case CENTER_HOLD:
                if (buttonsPressed.b1) {
                    //resetInactivityTimer();
                    generate_wait(BUTTON_POLLING_DELAY);
                    resetButtonsState();
                    if (generation[j]==&a1BPP_UNCOMP) {
                        j++;
                        Graphics_drawImage(gc,&v1BPP_UNCOMP,pos_x2,pos_y2);
                        pos_x2=pos_x2+IMAGES_WIDTH;
                        continue;
                    } else {
                        j=0;
                        Graphics_drawImage(gc,&x1BPP_UNCOMP,pos_x2,pos_y2);
                        generate_wait(1000);
                        Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
                        Graphics_fillRectangle(gc,&clearLine);
                        Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
                        pos_x2=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
                        continue;
                    }
                } else {
                    if (buttonsPressed.b2) {
                        //resetInactivityTimer();
                        generate_wait(BUTTON_POLLING_DELAY);
                        resetButtonsState();
                        if (generation[j]==&b1BPP_UNCOMP) {
                            j++;
                            Graphics_drawImage(gc,&v1BPP_UNCOMP,pos_x2,pos_y2);
                            pos_x2=pos_x2+IMAGES_WIDTH;
                            continue;
                        } else {
                            j=0;
                            Graphics_drawImage(gc,&x1BPP_UNCOMP,pos_x2,pos_y2);
                            generate_wait(1000);
                            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
                            Graphics_fillRectangle(gc,&clearLine);
                            Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
                            pos_x2=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
                            continue;
                        }
                    }
                }
                break;
            case LINE_UP:
                //resetInactivityTimer();
                if (generation[j]==&up_arrow1BPP_UNCOMP) {
                    j++;
                    Graphics_drawImage(gc,&v1BPP_UNCOMP,pos_x2,pos_y2);
                    pos_x2=pos_x2+IMAGES_WIDTH;
                    continue;
                } else {
                    j=0;
                    Graphics_drawImage(gc,&x1BPP_UNCOMP,pos_x2,pos_y2);
                    generate_wait(1000);
                    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
                    Graphics_fillRectangle(gc,&clearLine);
                    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
                    pos_x2=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
                    continue;
                }
            case LINE_DOWN:
                //resetInactivityTimer();
                if (generation[j]==&down_arrow1BPP_UNCOMP) {
                    j++;
                    Graphics_drawImage(gc,&v1BPP_UNCOMP,pos_x2,pos_y2);
                    pos_x2=pos_x2+IMAGES_WIDTH;
                    continue;
                } else {
                    j=0;
                    Graphics_drawImage(gc,&x1BPP_UNCOMP,pos_x2,pos_y2);
                    generate_wait(1000);
                    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
                    Graphics_fillRectangle(gc,&clearLine);
                    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
                    pos_x2=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
                    continue;
                }
            case LINE_LEFT:
                //resetInactivityTimer();
                if (generation[j]==&left_arrow1BPP_UNCOMP) {
                    j++;
                    Graphics_drawImage(gc,&v1BPP_UNCOMP,pos_x2,pos_y2);
                    pos_x2=pos_x2+IMAGES_WIDTH;
                    continue;
                } else {
                    j=0;
                    Graphics_drawImage(gc,&x1BPP_UNCOMP,pos_x2,pos_y2);
                    generate_wait(1000);
                    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
                    Graphics_fillRectangle(gc,&clearLine);
                    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
                    pos_x2=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
                    continue;
                }
            case LINE_RIGHT:
                //resetInactivityTimer();
                if (generation[j]==&right_arrow1BPP_UNCOMP) {
                    j++;
                    Graphics_drawImage(gc,&v1BPP_UNCOMP,pos_x2,pos_y2);
                    pos_x2=pos_x2+IMAGES_WIDTH;
                    continue;
                } else {
                    j=0;
                    Graphics_drawImage(gc,&x1BPP_UNCOMP,pos_x2,pos_y2);
                    generate_wait(1000);
                    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
                    Graphics_fillRectangle(gc,&clearLine);
                    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
                    pos_x2=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
                    continue;
                }
            }
        }
        pos_x=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
        pos_y=(DISPLAY_SIZE_Y/2)-(IMAGES_WIDTH/2)-(IMAGES_BOTTOM_MARGIN/2);
        pos_y2=pos_y+IMAGES_BOTTOM_MARGIN;
        pos_x2=IMAGES_WIDTH/(ACTION_GENERATION_NUMBER*2);
        clearScreen(gc);
    }
    char* endMessage[]=END_MESSAGE_TEXT;
    printTitleMessage(endMessage,END_MESSAGE_DIMENSION,gc);
    generate_wait(2000);
    clearScreen(gc);
    stopADCconversions();
    stopInactivityTimer();
    return TASK_COMPLETED;
}

void inactivityHandler() {
    inactivity_status=true;
}

void resetInactivityTimer() {
    inactivity_status=false;
    disable_timer(inactivity_timer);
    inactivity_timer=NONE;
    inactivity_timer=generate_delay(INACTIVITY_TIME,&inactivityHandler);
}
bool getInactivityTimerStatus() {
    return inactivity_status;
}

void stopInactivityTimer() {
    disable_timer(inactivity_timer);
    inactivity_timer=NONE;
}

void printTitleMessage(char* message[],int lines,Graphics_Context* gc) {
    if (lines==0) return;
    clearScreen(gc);
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

void clearScreen(Graphics_Context* gc) {
    Graphics_Rectangle fillRectangle;
    fillRectangle.xMin = 0;
    fillRectangle.xMax = DISPLAY_SIZE_X-1;
    fillRectangle.yMin = 0;
    fillRectangle.yMax = DISPLAY_SIZE_Y-1;
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_BLACK);
    Graphics_fillRectangle(gc, &fillRectangle);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
}

void printMessage(char* message[],int lines,Graphics_Context* gc) {
    clearScreen(gc);
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

joystick_area getJoyArea() {
    joystick sampledPosition=getJoyValue();
    if (((sampledPosition.joyXvalue>JOYPAD_CENTER_AREA_POSITION_X) && (sampledPosition.joyXvalue<(JOYPAD_CENTER_AREA_POSITION_X+JOYPAD_CENTER_AREA_DELTA_X)))&&((sampledPosition.joyYvalue>JOYPAD_CENTER_AREA_POSITION_Y) && (sampledPosition.joyYvalue<(JOYPAD_CENTER_AREA_POSITION_Y+JOYPAD_CENTER_AREA_DELTA_Y)))) {
        return CENTER;
    }
    if (((sampledPosition.joyXvalue>JOYPAD_LEFT_AREA_POSITION_X) && (sampledPosition.joyXvalue<(JOYPAD_LEFT_AREA_POSITION_X+JOYPAD_LEFT_AREA_DELTA_X)))&&((sampledPosition.joyYvalue>JOYPAD_LEFT_AREA_POSITION_Y) && (sampledPosition.joyYvalue<(JOYPAD_LEFT_AREA_POSITION_Y+JOYPAD_LEFT_AREA_DELTA_Y)))) {
            return LEFT_CORNER;
    }
    if (((sampledPosition.joyXvalue>JOYPAD_RIGHT_AREA_POSITION_X) && (sampledPosition.joyXvalue<(JOYPAD_RIGHT_AREA_POSITION_X+JOYPAD_RIGHT_AREA_DELTA_X)))&&((sampledPosition.joyYvalue>JOYPAD_RIGHT_AREA_POSITION_Y) && (sampledPosition.joyYvalue<(JOYPAD_RIGHT_AREA_POSITION_Y+JOYPAD_RIGHT_AREA_DELTA_Y)))) {
            return RIGHT_CORNER;
    }
    if (((sampledPosition.joyXvalue>JOYPAD_TOP_AREA_POSITION_X) && (sampledPosition.joyXvalue<(JOYPAD_TOP_AREA_POSITION_X+JOYPAD_TOP_AREA_DELTA_X)))&&((sampledPosition.joyYvalue>JOYPAD_TOP_AREA_POSITION_Y) && (sampledPosition.joyYvalue<(JOYPAD_TOP_AREA_POSITION_Y+JOYPAD_TOP_AREA_DELTA_Y)))) {
            return UP_CORNER;
    }
    if (((sampledPosition.joyXvalue>JOYPAD_BOTTOM_AREA_POSITION_X) && (sampledPosition.joyXvalue<(JOYPAD_BOTTOM_AREA_POSITION_X+JOYPAD_BOTTOM_AREA_DELTA_X)))&&((sampledPosition.joyYvalue>JOYPAD_BOTTOM_AREA_POSITION_Y) && (sampledPosition.joyYvalue<(JOYPAD_BOTTOM_AREA_POSITION_Y+JOYPAD_BOTTOM_AREA_DELTA_Y)))) {
            return DOWN_CORNER;
    }
    if (((sampledPosition.joyXvalue>JOYPAD_LEFT_TRAJECTORY_AREA_POSITION_X) && (sampledPosition.joyXvalue<(JOYPAD_LEFT_TRAJECTORY_AREA_POSITION_X+JOYPAD_LEFT_TRAJECTORY_AREA_DELTA_X)))&&((sampledPosition.joyYvalue>JOYPAD_LEFT_TRAJECTORY_AREA_POSITION_Y) && (sampledPosition.joyYvalue<(JOYPAD_LEFT_TRAJECTORY_AREA_POSITION_Y+JOYPAD_LEFT_TRAJECTORY_AREA_DELTA_Y)))) {
            return LEFT_TRAJECTORY;
    }
    if (((sampledPosition.joyXvalue>JOYPAD_RIGHT_TRAJECTORY_AREA_POSITION_X) && (sampledPosition.joyXvalue<(JOYPAD_RIGHT_TRAJECTORY_AREA_POSITION_X+JOYPAD_RIGHT_TRAJECTORY_AREA_DELTA_X)))&&((sampledPosition.joyYvalue>JOYPAD_RIGHT_TRAJECTORY_AREA_POSITION_Y) && (sampledPosition.joyYvalue<(JOYPAD_RIGHT_TRAJECTORY_AREA_POSITION_Y+JOYPAD_RIGHT_TRAJECTORY_AREA_DELTA_Y)))) {
            return RIGHT_TRAJECTORY;
    }
    if (((sampledPosition.joyXvalue>JOYPAD_TOP_TRAJECTORY_AREA_POSITION_X) && (sampledPosition.joyXvalue<(JOYPAD_TOP_TRAJECTORY_AREA_POSITION_X+JOYPAD_TOP_TRAJECTORY_AREA_DELTA_X)))&&((sampledPosition.joyYvalue>JOYPAD_TOP_TRAJECTORY_AREA_POSITION_Y) && (sampledPosition.joyYvalue<(JOYPAD_TOP_TRAJECTORY_AREA_POSITION_Y+JOYPAD_TOP_TRAJECTORY_AREA_DELTA_Y)))) {
            return UP_TRAJECTORY;
    }
    if (((sampledPosition.joyXvalue>JOYPAD_BOTTOM_TRAJECTORY_AREA_POSITION_X) && (sampledPosition.joyXvalue<(JOYPAD_BOTTOM_TRAJECTORY_AREA_POSITION_X+JOYPAD_BOTTOM_TRAJECTORY_AREA_DELTA_X)))&&((sampledPosition.joyYvalue>JOYPAD_BOTTOM_TRAJECTORY_AREA_POSITION_Y) && (sampledPosition.joyYvalue<(JOYPAD_BOTTOM_TRAJECTORY_AREA_POSITION_Y+JOYPAD_BOTTOM_TRAJECTORY_AREA_DELTA_Y)))) {
            return DOWN_TRAJECTORY;
    }

    return OTHER;
}


joystick_movement getJoyMovement() {
    bool detected_movement=false;
    joystick_movement predictedMovement=UNDEFINED_MOVEMENT;
    joystick_area joystickSampledArea=OTHER;
    while (!detected_movement) {
        joystickSampledArea=getJoyArea();
        switch(predictedMovement) {
                case CENTER_HOLD:
                    switch(joystickSampledArea) {
                    case UP_CORNER:
                        predictedMovement=LINE_UP;
                        detected_movement=true;
                        break;
                    case UP_TRAJECTORY:
                        predictedMovement=LINE_UP;
                        break;
                    case DOWN_CORNER:
                        predictedMovement=LINE_DOWN;
                        detected_movement=true;
                        break;
                    case DOWN_TRAJECTORY:
                        predictedMovement=LINE_DOWN;
                        break;
                    case LEFT_CORNER:
                        predictedMovement=LINE_LEFT;
                        detected_movement=true;
                        break;
                    case LEFT_TRAJECTORY:
                        predictedMovement=LINE_LEFT;
                        break;
                    case RIGHT_CORNER:
                        predictedMovement=LINE_RIGHT;
                        detected_movement=true;
                        break;
                    case RIGHT_TRAJECTORY:
                        predictedMovement=LINE_RIGHT;
                        break;
                    case CENTER:
                        return CENTER_HOLD;
                    default:
                        predictedMovement=UNDEFINED_MOVEMENT;
                        break;
                    }
                    break;

                case LINE_UP:
                    switch(joystickSampledArea) {
                    case UP_TRAJECTORY:
                        break;
                    case UP_CORNER:
                        detected_movement=true;
                        break;
                    default:
                        predictedMovement=UNDEFINED_MOVEMENT;
                        break;
                    }
                    break;

                case LINE_DOWN:
                    switch(joystickSampledArea) {
                    case DOWN_TRAJECTORY:
                        break;
                    case DOWN_CORNER:
                        detected_movement=true;
                        break;
                    default:
                        predictedMovement=UNDEFINED_MOVEMENT;
                        break;
                    }
                    break;

                case LINE_LEFT:
                    switch(joystickSampledArea) {
                    case LEFT_TRAJECTORY:
                        break;
                    case LEFT_CORNER:
                        detected_movement=true;
                        break;
                    default:
                        predictedMovement=UNDEFINED_MOVEMENT;
                        break;
                    }
                    break;

                case LINE_RIGHT:
                    switch(joystickSampledArea) {
                    case RIGHT_TRAJECTORY:
                        break;
                    case RIGHT_CORNER:
                        detected_movement=true;
                        break;
                    default:
                        predictedMovement=UNDEFINED_MOVEMENT;
                        break;
                    }
                    break;

                default:
                    if (joystickSampledArea==CENTER) {
                        predictedMovement=CENTER_HOLD;
                    }
                    break;

                }
        generate_wait(JOYPAD_SAMPLE_RATE);


    }
    return predictedMovement;
}




