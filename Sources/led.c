/* Source copied from CSCIE-92 class sample code */
#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "led.h"
#include "leddriver.h"
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
    printf("ledwrite ch = %d\n", ch);
    leds[fd].write(ch); 
    return 0; 
}
