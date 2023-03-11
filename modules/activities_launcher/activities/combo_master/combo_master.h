
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

state combo_master_start(Graphics_Context* gc);

#endif
