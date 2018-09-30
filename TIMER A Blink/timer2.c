/* Rowan University
 * File: timer2.c
 * Author: Jan Garcia
 * Course: Intro to Embedded Systems
 * Section: 1
 * Creation Data: 9/25/18
 * Lab 2 - TimerA Blink
 * Board - MSP430F5529
 *
 * Description: This code blinks two LEDs connected to P1.0 and P4.7 on the MSP430F5529 board.
 * The TA0CCR0 is valued at 20000 to count up at this value before it drops to 0. The TimerA module
 * is used in up mode with an ACLK source and pre-divider of 2.
 *
 * The divider takes 20000 and divides it by 2 -> 10000. The new value for TA0CCR0 is 10000.
 * In Timer0 A0 interrupt service routine (ISR) the red LED is toggle first at a rate of
 * 10000 / (2*10000) = 0.5Hz and the interrupt is triggered at 12kHz / 20000 = 0.6 -> 1/0.6 = 1.67 secs.
 * The green LED will trigger after 2 flashes later because of the counter placed inside the ISR (0.5 * 4 = 2).
 */

#include <msp430.h> 


/**
 * main.c
 */

int i = 0; // Control variable

int main(void)
{

    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer


    P1DIR |= BIT0;  // P1.0 set as output
    P1OUT &= ~BIT0;  // P1.0 set OFF (Red LED)
    P4DIR |= BIT7;  // P1.6 set as output
    P4OUT &= ~BIT7;  // P4.7 set OFF (Green LED)


    TA0CCR0 = 20000;  // Counter value
    TA0CCTL0 = CCIE;  // Enable Timer0_A interrupts
    TA0CTL = TASSEL_1 + MC_1 + ID_1;  // ACLK, Up Mode (Counts to TA0CCR0), ID_1: 20000/2 = 10000Hz

    _BIS_SR(LPM0_bits + GIE);  // Enter Low power mode 0 with interrupts enabled
}

#pragma vector=TIMER0_A0_VECTOR  // Timer0 A0 interrupt service routine
   __interrupt void Timer0_A0 (void)
   {

        i++;
        P1OUT ^= BIT0;  // P1.0 Toggle (Red LED)

       if (i == 4)
       {
        P4OUT ^= BIT7;  // P4.7 Toggle (Green LED)
        i = 0;
       }
   }
