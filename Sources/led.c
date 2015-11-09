/* Source copied from CSCIE-92 class sample code */
#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "led.h"
#include "leddriver.h"
#include "common.h"
typedef unsigned long uintptr_t; 

led_t leds[NUM_OF_LEDS] = { 
    {ledOrangeConfig, ledOrangeWrite}, 
    {ledYellowConfig, ledYellowWrite}, 
    {ledGreenConfig, ledGreenWrite}, 
    {ledBlueConfig, ledBlueWrite}, 
};

int led_init(void * minor_num){ 
    int fd = (int) (uintptr_t) minor_num; 
    leds[fd].init(); 
    return 0;
}

int led_write(int ch, void *minor_num){ 
    int fd = (int) (uintptr_t) minor_num; 
    char print_string[1000]; 
    sprintf(print_string, "ledwrite ch = %d\n", ch);
    write_string(print_string, mystdout); 
    leds[fd].write(ch); 
    return 0; 
}
