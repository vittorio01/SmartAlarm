#include "combo_master.h"


state combo_master_start(Graphics_Context* gc) {
    currentState=RUNNING;
    startADCconversions();
    char* title[TITLE_DIMENSION];
    sprintf(title,TITLE_TEXT);
    Graphics_drawString(gc, (int8_t*) title,TITLE_DIMENSION,TITLE_POSITION_X, TITLE_POSITION_Y,OPAQUE_TEXT);

    //Graphics_drawImage(gc, &down_arrow1BPP_UNCOMP, TITLE_POSITION_X, TITLE_POSITION_Y,);
    stopADCconversions();
    return currentState;
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
        generate_wait(JOYPAD_SAMPLE_RATE);
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
                        break;
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


    }
    return predictedMovement;
}




