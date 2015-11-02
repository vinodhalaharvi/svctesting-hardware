/* Source copied from CSCIE-92 class sample code */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "derivative.h"
#include "uartdriver.h"
#include "uart.h"
#include "delay.h"

uart_t uarts[NUM_OF_UARTS] = { 
    {uart_driver_init, uart_driver_write, uart_driver_read}, 
};


int uart_init(void * minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    uarts[fd].init();
    return 0;
}

int uart_read(void *minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    uarts[fd].read(); 
    return 0; 
}

int uart_write(int ch, void *minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    uarts[fd].write(ch); 
    return 0; 
}

