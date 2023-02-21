#ifndef __ACTIVITIES_LAUNCHER__
#define __ACTIVITIES_LAUNCHER__

#include <stdbool.h>

typedef enum {RUNNING, USER_INACTIVE, TASK_COMPLETED, TASK_CLOSED, UNDEFINED} state;
typedef state (*func_type)(void);

state launch_game();
const int activitiesNumber = 1;
//state (*activityList[activitiesNumber])();
func_type activityList[1];
#endif
