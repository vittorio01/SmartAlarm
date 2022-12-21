#include "msp.h"
#include "modules/ringtones_manager/ringtones.h"
#include "modules/activities_launcher/activities.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
}

//end