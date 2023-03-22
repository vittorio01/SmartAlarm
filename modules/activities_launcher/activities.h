#ifndef __ACTIVITIES_LAUNCHER__
#define __ACTIVITIES_LAUNCHER__

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <modules/hardware/hardware.h>

typedef enum {USER_INACTIVE, TASK_COMPLETED, UNDEFINED} state;
typedef state (*func_type)(Graphics_Context* gc);

#define ACTIVITIES_NUMBER 1

/* add activities start functions here */
state combo_master_start(Graphics_Context* gc);

state launch_game();

#endif
