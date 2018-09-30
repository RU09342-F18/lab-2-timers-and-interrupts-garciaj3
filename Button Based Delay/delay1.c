/* Rowan University
 * File: delay1.c
 * Author: Jan Garcia
 * Course: Intro to Embedded Systems
 * Section: 1
 * Creation Data: 9/25/18
 * Lab 2 - Button Based Delay
 * Board - MSP430G2553
 *
 * Description: This code uses the timer module to generate a PWM waveform which is used and
 * control by a button connected to P1.3 to manage the intensity of the LED connected to P1.6.
 *
 * The duty cycle of the pwm starts at 0, since TACCR1 = 0. The value is then increases through the
 * while loop and if statements until it reaches TACCR0 = 10000. The value is incremented by steps of 100.
 * The value is then decreased back to 0 and goes back up again until it reaches 10000.
 * The value TACCR1 is basically creating the pwm duty cycle at changes of 10%. The delay of cycles is
 * added to see the brightness/dimming of the LED  each time the button is being hold down.
 *
 */


#include <msp430.h> 

/**
 * main.c
 */
#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P1DIR |= BIT6; // P1.6 as output
    P1OUT &= ~(BIT6); // LED OFF
    P1SEL |= BIT6; // P1SEL <- BIT6 must be 1 to create the pwm

    TACCR0 = 10000; //Setting up the PWM Frequency or count value
    TACCR1 = 0; //Duty cycle will start at 0
    TACCTL1 |= OUTMOD_7; //Using Reset/Set mode to generate PWM wave
    TACTL |= TASSEL_2 + MC_1; //Configuring the timer to use SMCLK and count in UP mode

    int pwm = 0, l = 100; //Initializing required variables
    while(1)
    {
        if((P1IN & BIT3) == 0) // Checks pin P1.3 if it has been reset then toggles the LED.
               {

        __delay_cycles(20000); //Wait before changing the duty cycles, for smooth variation
        pwm += l; //Change the duty cycle

        if(pwm == 10000)
            {
                l =- 100;//If duty cycle is at maximum, start decreasing it
            }
        if(pwm==0)
            {
                l=100; //If duty cycle is at minimum, start increasing it
            }

         TACCR1=pwm; //Set the duty cycles in the CCR1
               }
    }

    return 0;
}

