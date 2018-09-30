# Button Based Delay - MSP430G2553 & MSP430FR2311
The files provided in this folder are **delay1.c** and **delay2.c** that both uses PWM waveform to control intensity of the LED by a button in the development boards. The MSP430G2553 c.file is named delay1.c and the MSP430FR2311 c.file is named delay2.c. 

### MSP430G2553
**Description** : This code uses the timerA0 module to generate a PWM waveform which is used and control by a button connected to P1.3 to manage the intensity of the LED connected to P1.6. The timer is configured to use SMCLK and in count UP mode. The duty cycle of the pwm starts at 0, since TACCR1 = 0. The value is then increases through the while loop and if statements until it reaches TACCR0 = 10000.

```c
TACCR0 = 10000; //Setting up the PWM Frequency or count value
TACCR1 = 0; //Duty cycle will start at 0
TACCTL1 |= OUTMOD_7; //Using Reset/Set mode to generate PWM wave
TACTL |= TASSEL_2 + MC_1; //Configuring the timer to use SMCLK and count in UP mode
```   
The value is incremented by steps of 100. The value is then decreased back to 0 and goes back up again until it reaches 10000. The value TACCR1 is basically creating the pwm duty cycle at changes of 1%. The delay of cycles is added to see the brightness/dimming of the LED  each time the button is being hold down.

```c
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
```
### MSP430FR2311
**Description** : This code uses the timerB1 module to generate a PWM waveform which is used and control by a button connected to P1.1 that manage the intensity of the LED connected to P2.0. The timerB is configured to use SMCLK and in count UP mode and the Reset/Set mode is used to generate PWM wave.
```c
    TB1CCR0 = 10000; //Setting up the PWM Frequency or count value using TimerB1
    TB1CCR1 = 0; //Duty cycle will start at 0
    TB1CCTL1 |= OUTMOD_7; //Using Reset/Set mode to generate PWM wave
    TB1CTL = TBSSEL__SMCLK | MC__UP; //Configuring the timerB to use SMCLK and count in UP mode
```
The duty cycle of the pwm starts at 0, since TB1CCR1 = 0. The value is then increases through the while loop and if statements until it reaches TB1CCR0 = 10000. The value is incremented by steps of 100. The value is then decreased back to 0 and goes back up again until it reaches 10000. The value TB1CCR1 is basically creating the pwm duty cycle at changes of 1%. The delay of cycles is added to see the brightness/dimming of the LED  each time the button is being hold down. 

```c
  int pwm = 0, l = 100; //Initializing required variables
    while(1)
    {
        if((P1IN & BIT1) == 0) // Checks pin P1.1 if it has been reset then toggles the LED.
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

         TB1CCR1=pwm; //Set the duty cycles in the CCR1
               }
    }
```
### Watchdog Timers
Both are set to have their watchdog timers off so that the controllers do not reset everytime when they're using interrupts. In fact, watchdog timers keeps track of any abnormal behavior from the program. If the program fails and it "crashes," then the watchdog timer will trigger a reset and force the program back to the beginning. This needs to be disable so that the function of the code works.

**Regard Unlocking Pins** : In the FR series boards, the GPIO pins must be unlock using a specfic line of code contained in the file. This line of code helps from disconnecting the output pins from the board and helps with power consumption. 
