#include "ADC.h"

void ConfigureADC(void)
{
	/* ADC10 Control register 1
	 * INCH_7 = choose analog input A7
	 * INCH_10 = choose the temperature sensor as the analog input
	 *
	 * ADC10DIV_3 = divide ADC clock by 4 (for temperature sensor)
	 */
#if (ADC10_MODE == ADC10_A7)
	ADC10CTL1 = (INCH_7 | ADC10DIV_3);
	ADC10AE0 |= ADC10_A7_BIT; 	// Enable ADC10 A7
#else
	ADC10CTL1 = (INCH_10 | ADC10DIV_3);
#endif

	/* ADC10 Control register 0
	 * SREF_0: Choose Vcc reference for analog inputs
	 * SREF_1: Choose 1.5V reference for temperature sensor
	 *
	 * ADC10SHT_3 = 64 × ADC10CLKs (for temperature sensor)
	 */
#if (ADC10_MODE == ADC10_A7)
	ADC10CTL0 = (SREF_0 | ADC10SHT_3 | ADC10ON);
#else
	ADC10CTL0 = (SREF_1 | ADC10SHT_3 | REFON | ADC10ON);
#endif

	_delay_cycles(1000);			// Wait for the ADC to adjust and stabilize
	ADC10CTL0 |=  (ENC | ADC10SC);	// Enable and begin sampling and conversion
}
