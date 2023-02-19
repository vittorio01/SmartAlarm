#include "msp.h"
#include "modules/ringtones_manager/ringtones_manager.h"
#include "modules/activities_launcher/activities.h"
#include <modules/hardware/hardware.h>

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
}

//end
