#ifndef __ACTIVITIES_LAUNCHER__
#define __ACTIVITIES_LAUNCHER__

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


typedef enum {RUNNING, USER_INACTIVE, TASK_COMPLETED, TASK_CLOSED, UNDEFINED} state;
typedef state (*func_type)(); //manca il passaggio del graphic context 

state launch_game();

#endif
