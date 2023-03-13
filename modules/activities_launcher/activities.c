#include "activities.h"



state launch_game(){
    const int activitiesNumber = 1;
    func_type activityList[activitiesNumber];
    time_t t;
    srand((unsigned) time(&t));
    int i = rand() % activitiesNumber;
    return activityList[i]();//manca il passaggio del graphic context

}
