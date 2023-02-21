#include "activities.h"

state launch_game(){
    int i = rand() % activitiesNumber;
    return activityList[i]();
; 
}