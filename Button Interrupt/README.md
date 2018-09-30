# Button Interrupt - MSP430G2553 & MSP432P401R
The files provided in this folder are **interrupt1.c** and **interrupt2.c** that both uses interrupts to toggle an LED with buttons in the development boards. The MSP430G2553 c.file is named interrupt1.c and the MSP432P401R c.file is named interrupt2.c. 

### MSP430G2553
**Description** : The MSP430G2553 uses an interrupt to toggle the P1.0 green LED ON only when depressing the button. The code utilizes a for loop and an interrupt to allow the LED to light up when depressing the button. The flag is set to check when the button is press and triggers the interrupt. The interrupt is triggered after the button is toggle from HitoLow, and changes the state of the LED ON. THe flag is then cleared after the letting go of the button and the main program is set at infinite loop.

### MSP432P401R
**Description** : The MSP432P401R uses interrupts to toggle the P1.0 red LED ON and OFF when the button is press. The code utilizes an interrupt to detect when the button is press for P1.1 and then toggles the LED P1.0. The P1.0 LED is configured as an output and P1.1 (switch) as input with pull-up resistor. The rest of the other pins are configured as output low. The flag is then set to check when the button is press and triggers the interrupt. A delay cycles of 500000 is used to compensate the switch debouncing effect. This delay waits for an  approximate 0.5 secs until it lets the LED turn ON. 

### Watchdog Timers
Both are set to have their watchdog timers off so that the controllers do not reset everytime when they're using interrupts. In fact, watchdog timers keeps track of any abnormal behavior from the program. If the program fails and it "crashes," then the watchdog timer will trigger a reset and force the program back to the beginning. This needs to be disable so that the function of the code works.
