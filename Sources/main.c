#include <stdio.h>
#include "svc.h"
#include "led.h"
#include "delay.h"
#include "pushbutton.h"

extern void svcHandler(void);

int verify_led(void) {
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
		SVCLedWrite(1, 1);
		SVCLedWrite(1, 2);
		SVCLedWrite(1, 3);
		delay(delayCount * 3);	
		SVCLedWrite(0, 0);
		SVCLedWrite(0, 1);
		SVCLedWrite(0, 2);
		SVCLedWrite(0, 3);
	}
	printf("FlashLED Project Completed\n");
	return 0;
}


int verify_pushbutton(void) {
	printf("Pushbuttons Project Starting\n");
    unsigned i; 
    for (i = 0; i < NUM_OF_LEDS; ++i) {
        SVCLedInit(i); 
        SVCPushButtonInit(i); 
    
    }
	while(1) {
		if(SVCPushButtonRead(0)) {
			SVCLedWrite(0,3);
		} else {
			SVCLedWrite(1,3);
		}
		if(SVCPushButtonRead(1)) {
			SVCLedWrite(0,0);
		} else {
			SVCLedWrite(1,0);
		}
	}
	printf("Pushbuttons Project Completed\n");
	return 0;
}

void uart_write_string(char *p) {
	while(*p) {
		uart_writer(*p++);
	}
}


int verify_uart(void){
	const unsigned long int delayCount = 0x7ffff;
	printf("SerialIO Project Starting\n");
	uart_write_string("SerialIO Project Starting\r\n");
	uart_write_string("Waiting for character from UART2");
	while(!uartGetcharPresent(UART2_BASE_PTR)) {
		uart_write('.');
		delay(delayCount);
	}
	uart_write_string("\r\nReceived character from UART2: '");
	uart_write_string("'\r\n");
	uart_write_string("SerialIO Project Completed\r\n");
	printf("SerialIO Project Completed\n");
	return 0;
}

int verify_lcdc(void){ 
}

int main(int argc, char *argv[])
{
    verify_pushbutton(); 
    return 0;
}
