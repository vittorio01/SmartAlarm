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

#define TITLE "COMBO MASTER!"
#define TITLE_DIMENSION 13
#define TITLE_SHOW_TIME 1500

state combo_master_start(Graphics_Context* gc) {
    currentState=RUNNING;

    char title[TITLE_DIMENSION]=TITLE;

    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_GRAY);
    Graphics_setFont(gc, &g_sFontCm18b);
    Graphics_drawString(gc, (int8_t*) title, TITLE_DIMENSION, TEXT_POSITION_X, TEXT_POSITION_Y, OPAQUE_TEXT);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_WHITE);
    drawTitle(gc, title);
    generate_wait(TITLE_SHOW_TIME);


}
