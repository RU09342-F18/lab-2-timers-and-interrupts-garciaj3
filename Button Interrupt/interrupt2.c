/* Rowan University
 * File: interrupt2.c
 * Author: Jan Garcia
 * Course: Intro to Embedded Systems
 * Section: 1
 * Creation Data: 9/25/18
 * Lab 2 - Button interrupt
 * Board - MSP432P401R
 *
 * Description: The MSP432P401R uses interrupts to toggle the P1.0 red
 * LED ON and OFF when the button is press.
 *
 * The code utilizes an interrupt to detect when the button is press for P1.1
 * and then toggles the LED P1.0. The flag is set to check when the button is press
 * and triggers the interrupt. A delay cycles of 500000 is used to compensate the
 * switch debouncing effect.
 *
 */

#include "msp.h"

int main(void)
{
    // Hold the watchdog

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // Configuring P1.0 as output and P1.1 (switch) as input with pull-up
    // resistor. Rest of pins are configured as output low.

    P1DIR |= ~BIT1; // Set P1.1 as Output GIPO
    P1OUT |= BIT1; // Set P1.1 as Output
    P1REN |= BIT1; // Enable pull-up resistor (P1.1 output high)
    P1SEL0 |= 0; // Default to simple I/O
    P1SEL1 |= 0; // Default to simple I/O
    P1IES |= BIT1; // Interrupt on high-to-low transition
    P1IFG |= 0;   // Clear all P1 interrupt flags
    P1IE |= BIT1; // Enable interrupt for P1.1

    // Enable Port P1 interrupts
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);


    // Enable PCM rude mode, which allows to device to enter LPM3 without waiting for peripherals
    PCM->CTL1 = PCM_CTL0_KEY_VAL | PCM_CTL1_FORCE_LPM_ENTRY;

    // Enable global interrupt
    __enable_irq();
}

/* Port1 ISR */
void PORT1_IRQHandler(void)
{

    // Toggling the output on the LED
    if(P1IFG & BIT1)
        P1OUT ^= BIT0;

    // Delay for switch debounce
    __delay_cycles(500000); // 1MHz / 500kHz = 0.5s delay

    P1IFG &= ~BIT1; // P1.1 clear IFG
}

