
#ifndef __TREASURE_HUNT_H__
#define __TREASURE_HUNT_H__
#include <stdlib.h>
#include <modules/hardware/hardware.h>
#include <modules/activities_launcher/activities.h>
#include <math.h>
#include <time.h>

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




#define MOVEMENTS_NUMBER 6
#define IMAGES_WIDTH    24

extern const tImage  v1BPP_UNCOMP2;

#define JOYPAD_SAMPLE_RATE    50

#define JOYPAD_MAX_RADIUS_VALUE     130
#define JOYPAD_MAX_Y_VALUE      JOYPAD_MAX_RADIUS_VALUE
#define JOYPAD_MAX_X_VALUE      JOYPAD_MAX_RADIUS_VALUE

#define DISPLAY_SIZE_X          128
#define DISPLAY_SIZE_Y          128

#define TITLE_FONT              &g_sFontCm20b
#define TITLE_SPACING           5
#define TITLE_TEXT              {"TREASURE","HUNT"}
#define TITLE_DIMENSION         2
#define TITLE_SHOW_TIME         2000

#define MESSAGE_FONT            &g_sFontCm12b
#define GAME_DESCRIPTION_TEXT1  {"Try to find ","the 'hidden ","treasure' using ", "the joypad ","and the color ","tips(red and yellow)"," ","Press A to skip"}
#define GAME_DESCRIPTION_TEXT1_DIMENSION 8
#define GAME_DESCRIPTION_SHOW_TIME       3000

#define MESSAGE_SPACING    2
#define MESSAGE_MARGIN_X   10
#define MESSAGE_MARGIN_Y   10

#define BUTTON_POLLING_DELAY    200

#define STAGE_GENERATION_NUMBER     4

#define END_MESSAGE_TEXT {"GAME","CLEAR!"};
#define END_MESSAGE_DIMENSION 2

#define INACTIVITY_TIME     32000

typedef struct {int x; int y} treasure;

void initJoypadSystem();
void stopInactivityTimer2();
void resetInactivityTimer2();
bool getInactivityTimerStatus2();
void printMessage2(char** message,int lines,Graphics_Context* gc);
void clearScreen2(Graphics_Context* gc);
void printTitleMessage2(char* message[],int lines,Graphics_Context* gc);
void inactivityHandler2();

void newTreasure(treasure* treasure);
void printRectangle(joystick position, Graphics_Context* gc, int color);
int checkPosition(joystick position, treasure treasure);

timerNumber inactivity_timer;
bool inactivity_status;

#endif
