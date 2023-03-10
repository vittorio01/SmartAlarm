
#ifndef __COMBO_MASTER_H__
#define __COMBO_MASTER_H__
#include <stdlib.h>
#include <modules/hardware/hardware.h>
#include <modules/activities_launcher/activities.h>

state currentState;

extern const tImage  down_arrow1BPP_UNCOMP;

state combo_master_start(Graphics_Context* gc);

#endif
