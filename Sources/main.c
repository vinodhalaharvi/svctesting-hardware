#include <stdio.h>
#include "led.h"
#include "delay.h"
#include "pushbutton.h"
#include "uart.h"
#include "mcg.h"
#include "sdram.h"
#include "lcdc.h"
#include "lcdcConsole.h"
#include "thermistor.h"
#include "uartdriver.h"
#include "potentiometer.h"
#include "svc.h"
#include "common.h"

#define FALSE 0
#define TRUE 1

void consoleDemo();

#define CHAR_EOF 4
extern void svcHandler(void);

int verify_led(void) {
    char print_string[1000]; 
    sprintf(print_string, "Starting SVCall project\n");
    write_string(print_string, mystdout); 
    svcInit_SetSVCPriority(7);
    //__asm("ldr r0,=73");
    //__asm("svc #4");
    const unsigned long int delayCount = 0x7ffff;
    sprintf(print_string, "FlashLED Project Starting\n");
    write_string(print_string, mystdout); 
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
    sprintf(print_string, "FlashLED Project Completed\n");
    write_string(print_string, mystdout); 
    return 0;
}


int verify_pushbutton(void) {
    char print_string[1000]; 
    sprintf(print_string, "Pushbuttons Project Starting\n");
    write_string(print_string, mystdout); 
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
    sprintf(print_string, "Pushbuttons Project Completed\n");
    write_string(print_string, mystdout); 
    return 0;
}

void uart_write_string(const char *p) {
    while(*p) {
        SVCUartWrite(*p++, 0);
    }
}

int verify_lcdc(){ 
    mcgInit();
    sdramInit();
    SVCUartInit(0); 
    SVCLcdcInit(0);
    while(1) {
        //this will eventually be using 
        //uart_read
        char ch = uartGetchar(UART2_BASE_PTR); 
        //char ch = uart_read(0);
        SVCUartWrite(ch, 0);
        SVCLcdcWrite(ch, 0); 
        if(ch == CHAR_EOF) {
            return 0;
        }
    }
    return 0;
}

int verify_uart(void){
    const unsigned long int delayCount = 0x7ffff;
    char print_string[1000]; 
    sprintf(print_string, "SerialIO Project Starting\n");
    write_string(print_string, mystdout); 
    uart_write_string("SerialIO Project Starting\r\n");
    uart_write_string("Waiting for character from UART2");
    while(!uart_input_present(0)) {
        SVCUartWrite('.', 0);
        delay(delayCount);
    }
    uart_write_string("\r\nReceived character from UART2: '");
    uart_write_string("'\r\n");
    uart_write_string("SerialIO Project Completed\r\n");
    sprintf(print_string, "SerialIO Project Completed\n");
    write_string(print_string, mystdout); 
    return 0;
}

int verify_potentiometer(void) {
   SVCPotentiometerInit(0);
   char print_string[1000]; 
   while(TRUE) { 
      sprintf(print_string, "pot: %4u\ttemp: %4u\n",
    		 SVCPotentiometerRead(0), 
    		 SVCPotentiometerRead(0));
    write_string(print_string, mystdout); 
   }
   return 0;
}

int verify_thermistor(void) {
   SVCThermistorInit(0);
   char print_string[1000]; 
   while(TRUE) { 
      sprintf(print_string, "pot: %4u\ttemp: %4u\n",
    		 SVCThermistorRead(0), 
    		 SVCThermistorRead(0));
      write_string(print_string, mystdout); 
   }
   return 0;
}

 
int verify_main()
{

    //verify_uart(); 
    verify_lcdc(); 
    //verify_thermistor(); 
    //verify_led(); 
    //verify_pushbutton(); 
    return 0;
}
