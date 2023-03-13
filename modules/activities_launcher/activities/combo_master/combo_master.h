
#ifndef __COMBO_MASTER_H__
#define __COMBO_MASTER_H__
#include <stdlib.h>
#include <modules/hardware/hardware.h>
#include <modules/activities_launcher/activities.h>

state currentState;

extern const tImage  down_arrow1BPP_UNCOMP;
extern const tImage  up_arrow1BPP_UNCOMP;
extern const tImage  left_arrow1BPP_UNCOMP;
extern const tImage  right_arrow1BPP_UNCOMP;
extern const tImage  rotation_clock_wise1BPP_UNCOMP;
extern const tImage  rotation_counter_clock_wise1BPP_UNCOMP;

#define JOYPAD_DELTA_MOVEMENT_X     5
#define JOYPAD_DELTA_MOVEMENT_Y     5

#define JOYPAD_MAX_Y_VALUE      128
#define JOYPAD_MAX_X_VALUE      128

#define JOYPAD_TOP_AREA_DELTA_X     20
#define JOYPAD_TOP_AREA_DELTA_Y     20
#define JOYPAD_TOP_AREA_POSITION_X  -JOYPAD_MAX_Y_VALUE-JOYPAD_TOP_AREA_DELTA_Y
#define JOYPAD_TOP_AREA_POSITION_Y  JOYPAD_TOP_AREA_DELTA_X/2

#define JOYPAD_BOTTOM_AREA_DELTA_X      20
#define JOYPAD_BOTTOM_AREA_DELTA_Y      20
#define JOYPAD_BOTTOM_AREA_POSITION_X   -JOYPAD_BOTTOM_AREA_DELTA_X/2
#define JOYPAD_BOTTOM_AREA_POSITION_Y   JOYPAD_BOTTOM_AREA_DELTA_Y-JOYPAD_MAX_Y_VALUE

#define JOYPAD_CENTER_AREA_DELTA_X      10
#define JOYPAD_CENTER_AREA_DELTA_Y      10
#define JOYPAD_CENTER_AREA_POSITION_X   -JOYPAD_CENTER_AREA_DELTA_X
#define JOYPAD_CENTER_AREA_POSITION_Y   -JOYPAD_CENTER_AREA_DELTA_Y

#define JOYPAD_LEFT_AREA_DELTA_X        20
#define JOYPAD_LEFT_AREA_DELTA_Y        20
#define JOYPAD_LEFT_AREA_POSITION_X     JOYPAD_LEFT_AREA_DELTA_X-JOYPAD_MAX_X_VALUE
#define JOYPAD_LEFT_AREA_POSITION_Y     -JOYPAD_LEFT_AREA_DELTA_Y/2

#define JOYPAD_RIGHT_AREA_DELTA_X       20
#define JOYPAD_RIGHT_AREA_DELTA_Y       20
#define JOYPAD_RIGHT_AREA_POSITION_X    JOYPAD_MAX_X_VALUE-JOYPAD_RIGHT_AREA_DELTA_X
#define JOYPAD_RIGHT_AREA_POSITION_Y    -JOYPAD_RIGHT_AREA_DELTA_Y/2

typedef enum{LINE_UP,LINE_DOWN,LINE_LEFT,LINE_RIGHT,WISE_CLOCK_ROTATION,COUNTER_WISE_CLOCK_ROTATION,UNDEFINED_MOVEMENT} joystick_movement;
typedef enum{CENTER,UP_CORNER,DOWN_CORNER,LEFT_CORNER,RIGHT_CORNER,OTHER} joystick_area;


state combo_master_start(Graphics_Context* gc);

void initJoypadSystem();

joystick sampledPosition;
joystick_movement predictedMovement;
joystick_area joystickArea;

/*  getJoyPosition() is used to read new values from joystick's ADC.
 *  If both two new coordinates don't exit from the specified bounds (square defined bounds), the return value doesn't change.
 *  With this system, all small changes of position are ignored.
*/
joystick getJoyPosition();

joystick_area getJoyArea();
joystick_movement

#endif
