// Manufacture provided device file
#include <msp430.h>
#include "timerA.h"
#include "ADC.h"
#include "LED.h"

// Local prototypes
void ConfigureClockModule();

void main(void)
{

	SetLEDState(LED1,OFF);
	SetLEDState(LED2,OFF);
	InitializeLEDPortPins();

	// Stop the watchdog timer, and configure the clock module.
	WDTCTL = WDTPW + WDTHOLD;
    ConfigureClockModule();
    ConfigureTimerA();
    ConfigureADC();

    _BIS_SR(GIE);

}



void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) using factory calibrations
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
}
