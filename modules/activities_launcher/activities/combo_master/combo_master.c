#include "combo_master.h"

/*
 * Combo master!
 *
 * To win this minigame the user has to repeat a given combination of movements in the correct order in a specific time interval.
 * The combination is visualized only once at game start. All possible movements and actions are:
 * -    up_arrow -> a vertical movement from the center to the upper position of the analog joypad
 * -    down_arrow -> a vertical movement from the center to the lower position of the analog joypad
 * -    left_arrow -> a horizontal movement from the center to the max left position of the analog joypad
 * -    right_arrow -> a horizontal movement from the center to the max right position of the analog joypad
 * -    circle_counter_wise -> a circular movement which start from the upper position, travel to the edge and returns to the upper position of the joypad
 * -    circle_wise_clock -> same as circle_counter_wise but in the opposite direction
 *
 * -    A -> a pressure of the first button is used for send the combination
 * -    B -> a pressure of the second button is used for delete the last action
 */



state combo_master_start(Graphics_Context* gc) {
    currentState=RUNNING;



    return currentState;
}

void initJoypadSystem() {
    sampledPosition.joyXvalue=0;
    sampledPosition.joyYvalue=0;
    predictedMovement=UNDEFINED_MOVEMENT;
    joystickArea=OTHER;
}

joystick getJoyPosition() {
    joystick newPosition=getJoyValue();
    if (((sampledPosition.joyXvalue - newPosition.joyXvalue)<JOYPAD_DELTA_MOVEMENT_X) && ((sampledPosition.joyXvalue - newPosition.joyXvalue)>-JOYPAD_DELTA_MOVEMENT_X)) {
       newPosition.joyXvalue=sampledPosition.joyXvalue;
    }
    if (((sampledPosition.joyYvalue - newPosition.joyYvalue)<JOYPAD_DELTA_MOVEMENT_Y) && ((sampledPosition.joyYvalue - newPosition.joyYvalue)>-JOYPAD_DELTA_MOVEMENT_Y)) {
        newPosition.joyYvalue=sampledPosition.joyYvalue;
    }
    return newPosition;
}

joystick_area getJoyArea() {
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
    return OTHER;
}




