#include "timerA.h"
#include <msp430.h>
#include "LED.h"

//values is an array that holds 8 samples from ADC10MEM
unsigned int values[8] = {0};
//position in array
int position = 0;
//avg_values is average of all values in the array
unsigned int average = 0;
unsigned int cumulative = 0;

int i = 0;


void ConfigureTimerA(void)
{
	TACCR0 = 2080;
	//Set up the timer
	TACTL = (TASSEL_2|ID_0|MC_1|TACLR);
	TACCTL0 = (CCIE);
}

unsigned int filter(unsigned int sum) {
	//turn on green LED when function starts
	SET_LED2_AS_AN_OUTPUT;
	TOGGLE_LED2;

	//calculate average
	sum = sum >> 3;
	//turn off green LED when function ends
	TOGGLE_LED2;
	return sum;
}

#pragma vector = TIMER0_A0_VECTOR
// Timer a interrupt service routine, add code here for IN LAB
	__interrupt void TimerA0_routine(void)
{
		//turn on red LED when sampling begins
		ADC10CTL0 |= ADC10SC;
		SET_LED1_AS_AN_OUTPUT;
		TOGGLE_LED1;

		cumulative -= values[i];
		//get samples from ADC10MEM
		values[i] = ADC10MEM;
		cumulative += values[i];

		i = (i + 1) & 7;
		//calculate average of samples
		if (i == 0) {
			average = filter(cumulative);
		}

		//turn off red LED when sampling ends


		TACCTL0 &= ~(CCIFG); //resets CCIFG so it does not infinitely loop
		ADC10CTL0 &= ~ADC10SC;
		TOGGLE_LED1;


}

