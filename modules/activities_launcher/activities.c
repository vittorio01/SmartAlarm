#include "activities.h"

state launch_game(Graphics_Context* gc){
    func_type activityList[ACTIVITIES_NUMBER]={&combo_master_start};
    time_t t;
    srand((unsigned) time(&t));
    int i = rand() % ACTIVITIES_NUMBER;
    return activityList[i](gc);

}
