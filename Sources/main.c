#include <stdio.h>
#include "svc.h"
#include "led.h"
#include "delay.h"
#include "pushbutton.h"
#include "uart.h"
#include "mcg.h"
#include "sdram.h"
#include "lcdc.h"
#include "lcdcConsole.h"
#include "thermistor.h"
#include "potentiometer.h"
#define FALSE 0
#define TRUE 1

void consoleDemo();

#define CHAR_EOF 4
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

void uart_write_string(const char *p) {
    while(*p) {
        uart_write(*p++, 0);
    }
}


void consoleDemo() {
    while(1) {
        char ch = uart_read(0);
        uart_write(ch, 0);
        lcdc_write(ch, 0); 
        if(ch == CHAR_EOF) {
            return;
        }
    }
}

int verify_lcdc(){ 
    mcgInit();
    sdramInit();
    uart_init(0); 
    lcdc_init(0);
    consoleDemo(); 
    return 0;
}

int verify_uart(void){
    const unsigned long int delayCount = 0x7ffff;
    printf("SerialIO Project Starting\n");
    uart_write_string("SerialIO Project Starting\r\n");
    uart_write_string("Waiting for character from UART2");
    while(!uart_input_present(0)) {
        uart_write('.', 0);
        delay(delayCount);
    }
    uart_write_string("\r\nReceived character from UART2: '");
    uart_write_string("'\r\n");
    uart_write_string("SerialIO Project Completed\r\n");
    printf("SerialIO Project Completed\n");
    return 0;
}

int verify_potentiometer(void) {
   potentiometer_init(0);
   while(TRUE) { 
      printf("pot: %4u\ttemp: %4u\n",
    		 potentiometer_read(0), 
    		 potentiometer_read(0));
   }
   return 0;
}

int verify_thermistor(void) {
   thermistor_init(0);
   while(TRUE) { 
      printf("pot: %4u\ttemp: %4u\n",
    		 thermistor_read(0), 
    		 thermistor_read(0));
   }
   return 0;
}

 
int main()
{
    //verify_pushbutton(); 
    //verify_uart(); 
    verify_lcdc(); 
    verify_thermistor(); 
    return 0;
}
