
#ifndef __COMBO_MASTER_H__
#define __COMBO_MASTER_H__
#include <stdlib.h>
#include <modules/hardware/hardware.h>
#include <modules/activities_launcher/activities.h>
#include <math.h>

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

state currentState;

extern const tImage  down_arrow1BPP_UNCOMP;
extern const tImage  up_arrow1BPP_UNCOMP;
extern const tImage  left_arrow1BPP_UNCOMP;
extern const tImage  right_arrow1BPP_UNCOMP;
extern const tImage  rotation_clock_wise1BPP_UNCOMP;
extern const tImage  rotation_counter_clock_wise1BPP_UNCOMP;

#define JOYPAD_APROXIMATION_RADIUS  5
#define JOYPAD_SAMPLING_RATE    100

#define JOYPAD_MAX_RADIUS_VALUE     128
#define JOYPAD_MAX_Y_VALUE      JOYPAD_MAX_RADIUS_VALUE
#define JOYPAD_MAX_X_VALUE      JOYPAD_MAX_RADIUS_VALUE


#define JOYPAD_TOP_AREA_DELTA_X     20
#define JOYPAD_TOP_AREA_DELTA_Y     20
#define JOYPAD_TOP_AREA_POSITION_X  JOYPAD_TOP_AREA_DELTA_X/2
#define JOYPAD_TOP_AREA_POSITION_Y  JOYPAD_MAX_Y_VALUE-JOYPAD_TOP_AREA_DELTA_Y

#define JOYPAD_BOTTOM_AREA_DELTA_X      20
#define JOYPAD_BOTTOM_AREA_DELTA_Y      20
#define JOYPAD_BOTTOM_AREA_POSITION_X   -JOYPAD_BOTTOM_AREA_DELTA_X/2
#define JOYPAD_BOTTOM_AREA_POSITION_Y   -JOYPAD_MAX_Y_VALUE

#define JOYPAD_CENTER_AREA_DELTA_X      10
#define JOYPAD_CENTER_AREA_DELTA_Y      10
#define JOYPAD_CENTER_AREA_POSITION_X   -JOYPAD_CENTER_AREA_DELTA_X/2
#define JOYPAD_CENTER_AREA_POSITION_Y   -JOYPAD_CENTER_AREA_DELTA_Y/2

#define JOYPAD_LEFT_AREA_DELTA_X        20
#define JOYPAD_LEFT_AREA_DELTA_Y        20
#define JOYPAD_LEFT_AREA_POSITION_X     -JOYPAD_MAX_X_VALUE
#define JOYPAD_LEFT_AREA_POSITION_Y     -JOYPAD_LEFT_AREA_DELTA_Y/2

#define JOYPAD_RIGHT_AREA_DELTA_X       20
#define JOYPAD_RIGHT_AREA_DELTA_Y       20
#define JOYPAD_RIGHT_AREA_POSITION_X    JOYPAD_MAX_X_VALUE-JOYPAD_RIGHT_AREA_DELTA_X
#define JOYPAD_RIGHT_AREA_POSITION_Y    -JOYPAD_RIGHT_AREA_DELTA_Y/2

#define JOYPAD_TOP_TRAJECTORY_AREA_DELTA_X      JOYPAD_CENTER_AREA_DELTA_X
#define JOYPAD_TOP_TRAJECTORY_AREA_DELTA_Y      JOYPAD_TOP_AREA_POSITION_Y-JOYPAD_TOP_TRAJECTORY_AREA_POSITION_Y
#define JOYPAD_TOP_TRAJECTORY_AREA_POSITION_X   JOYPAD_CENTER_AREA_POSITION_X
#define JOYPAD_TOP_TRAJECTORY_AREA_POSITION_Y   (JOYPAD_CENTER_AREA_DELTA_Y/2)

#define JOYPAD_BOTTOM_TRAJECTORY_AREA_DELTA_X       JOYPAD_CENTER_AREA_DELTA_X
#define JOYPAD_BOTTOM_TRAJECTORY_AREA_DELTA_Y       JOYPAD_BOTTOM_TRAJECTORY_AREA_POSITION_Y-JOYPAD_CENTER_AREA_POSITION_Y
#define JOYPAD_BOTTOM_TRAJECTORY_AREA_POSITION_X    JOYPAD_CENTER_AREA_POSITION_X
#define JOYPAD_BOTTOM_TRAJECTORY_AREA_POSITION_Y    JOYPAD_BOTTOM_AREA_POSITION_Y+JOYPAD_BOTTOM_AREA_DELTA_Y

#define JOYPAD_LEFT_TRAJECTORY_AREA_DELTA_X         JOYPAD_LEFT_TRAJECTORY_AREA_POSITION_X-(JOYPAD_CENTER_AREA_DELTA_X/2)
#define JOYPAD_LEFT_TRAJECTORY_AREA_DELTA_Y         JOYPAD_CENTER_AREA_POSITION_Y
#define JOYPAD_LEFT_TRAJECTORY_AREA_POSITION_X      JOYPAD_LEFT_AREA_POSITION_X+JOYPAD_LEFT_AREA_DELTA_X
#define JOYPAD_LEFT_TRAJECTORY_AREA_POSITION_Y      JOYPAD_CENTER_AREA_DELTA_Y

#define JOYPAD_RIGHT_TRAJECTORY_AREA_DELTA_X        JOYPAD_RIGHT_AREA_POSITION_X-JOYPAD_RIGHT_TRAJECTORY_AREA_POSITION_X
#define JOYPAD_RIGHT_TRAJECTORY_AREA_DELTA_Y        JOYPAD_CENTER_AREA_POSITION_Y
#define JOYPAD_RIGHT_TRAJECTORY_AREA_POSITION_X     (JOYPAD_CENTER_AREA_DELTA_X/2)
#define JOYPAD_RIGHT_TRAJECTORY_AREA_POSITION_Y     JOYPAD_CENTER_AREA_DELTA_Y

#define JOYPAD_CIRCLE_TRAJECTORY_AREA_RADIUS_DELTA  20
#define JOYPAD_CIRCLE_TRAJECTORY_AREA_RADIUS        JOYPAD_MAX_RADIUS_VALUE-JOYPAD_CIRCLE_TRAJECTORY_AREA_RADIUS_DELTA


typedef enum{LINE_UP,LINE_DOWN,LINE_LEFT,LINE_RIGHT,WISE_CLOCK_ROTATION,COUNTER_WISE_CLOCK_ROTATION,CENTER_HOLD,UNDEFINED_MOVEMENT} joystick_movement;
typedef enum{CENTER,UP_CORNER,DOWN_CORNER,LEFT_CORNER,RIGHT_CORNER,UP_TRAJECTORY,DOWN_TRAJECTORY,LEFT_TRAJECTORY,RIGHT_TRAJECTORY,WISE_CLOCK_TRAJECTORY,COUNTER_WISE_CLOCK_TRAJECTORY,OTHER} joystick_area;

void initJoypadSystem();

joystick sampledPosition;



/*  getJoyPosition() is used to read new values from joystick's ADC.
 *  If both two new coordinates don't exit from the specified bounds (square defined bounds), the return value doesn't change.
 *  With this system, all small changes of position are ignored.
*/
void updateJoyPosition();

joystick_area getJoyArea();
joystick_movement getJoyMovement();

#endif
