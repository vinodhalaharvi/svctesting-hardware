#include <stdio.h>
#include "svc.h"
#include "led.h"
#include "delay.h"

extern void svcHandler(void);
int main(void) {
	printf("Starting SVCall project\n");
	svcInit_SetSVCPriority(7);
	//__asm("ldr r0,=73");
	//__asm("svc #4");
	const unsigned long int delayCount = 0x7ffff;
	printf("FlashLED Project Starting\n");
	SVCLedInit(0);
	while(1) {
		delay(delayCount * 3);	
		SVCLedWrite(1, 0);
		delay(delayCount * 3);	
		SVCLedWrite(0, 0);
	}
	printf("FlashLED Project Completed\n");
	return 0;
}




