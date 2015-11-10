/**
 * intFlexTimerTest.c
 * FlexTimer interrupt test program
 * 
 * ARM-based K70F120M microcontroller board
 *   for educational purposes only
 * CSCI E-92 Spring 2014, Professor James L. Frankel, Harvard Extension School
 *
 * Written by James L. Frankel (frankel@seas.harvard.edu)
 */

/*
 * Important note:
 * 
 * The file Project_Settings -> Startup_Code -> kinetis_sysinit.c needs to be modified so
 * that a pointer to the flexTimer0Isr function is in the vector table at vector 78 (0x0000_0138)
 * for Flex Timer 0 (FTM0).
 * 
 * The following declaration needs to inserted earlier in the file:
 *   extern void flexTimer0Isr(void);
 *   
 * If using the GCC Toolchain, the vector table is named "InterruptVector", and the line:
 *   Default_Handler,		(comment delimiters removed) Vector 78: FTM0
 * needs to be changed to:
 *   flexTimer0Isr,		(comment delimiters removed) Vector 78: FTM0
 *   
 * If using the Freescale Toolchain, the vector table is named "__vect_table", and the line:
 *   (tIsrFunc)UNASSIGNED_ISR,    (comment delimiters removed) 78 (0x00000138) (prior: -)
 * needs to be changed to:
 *   (tIsrFunc)flexTimer0Isr,	  (comment delimiters removed) 78 (0x00000138) (prior: -)
 */

#include <stdio.h>
#include "intFlexTimerTest.h"
#include "delay.h"
#include "led.h"
#include "switchcmd.h"
#include "flexTimer.h"

/**
 * react to a user command (a button press).  commands are encoded
 * into several constants as defined in switchcmd.h.
 */
void processSwitchCmd(enum switchState cmd) {
	switch(cmd) {
	/* switch further away from the edge of the pc board */
	case switch1Down:
//		printf("Stopping FlexTimer0\n");

		flexTimer0Stop();
		break;
	/* switch closer to the edge of the pc board */
	case switch2Down:
//		printf("Starting FlexTimer0\n");

		flexTimer0Start();
		break;
	case noChange:
	case switch1Up:
	case switch2Up:
		break;        
	}  
}


/**
 * perform overall initialization.  the LCD, button states, scroll counters,
 * and timer are all set to known states and set in motion.
 */
void intFlexTimerTestInit(void) {
	ledInitAll();
	switchcmdInit();

	/* set interval to 1 second (128 1/128 second periods) */
	flexTimer0Init(128);
}

/**
 * this routine contains all actions to be performed when a FlexTimer 0
 * interrupt occurs.
 *
 * alternate turning the orange LED on and off with each interrupt.
 */
void flexTimer0Action(void) {
	static char ledState = 0;

	if((ledState ^= 1) == 1)
		ledOrangeOn();
	else
		ledOrangeOff();
}

/**
 * main entry point of program.
 * initialize all hardware.  enter infinite loop that busy-checks
 * for button presses and responds appropriately.
 */
int main(void) {
	enum switchState cmd;

	printf("Starting InterruptFlexTimerTest project\n");

	/* Perform all the necessary initializations */
	intFlexTimerTestInit();

	/* Allows interrupts (PRIMASK is cleared) -- this is also the default on reset */
	__asm("cpsie i");
	
	/* Endless main loop */
	while(1) {
		cmd = switchScan();
		if(cmd != noChange) {
			/* Delay for pushbutton debouncing */
			delay(3000);
			processSwitchCmd(cmd);
		}
	}
}
