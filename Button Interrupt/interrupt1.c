/* Rowan University
 * File: interrupt1.c
 * Author: Jan Garcia
 * Course: Intro to Embedded Systems
 * Section: 1
 * Creation Data: 9/25/18
 * Lab 2 - Button interrupt
 * Board - MSP430G2553
 *
 * Description: The  MSP430G2553 uses an interrupt to toggle the P1.0 green
 * LED ON only when depressing the button.
 *
 * The code utilizes a for loop and an interrupt to allow the LED
 * to light up when depressing the button. The interrupt is triggered after
 * the button is toggle from HitoLow, and changes the state of the LED ON.
 *
 */

#include <msp430.h> 

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop Watchdog timer
	P1DIR |= BIT0; // Set P1.0 as output.
	
	P1OUT = ~(BIT0); // Set LED off for output P1.0

	P1IE |= BIT3; // P1.3 interrupt enabled

	P1IFG &= ~BIT3; // P1.3 IFG cleared

	__enable_interrupt(); // Enable all interrupts
	for(;;) // Infinte loop
	{}
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR // defined vector
__interrupt void Port_1(void)
{
P1OUT ^= (BIT0); // P1.0 = toggle
P1IES ^= BIT3; // toggle the interrupt edge, the interrupt vector will be called when P1.3 goes from HitoLow
P1IFG &= ~BIT3; // P1.3 IFG cleared
}
