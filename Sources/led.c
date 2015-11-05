/* Source copied from CSCIE-92 class sample code */
#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "led.h"

void ledInit(){ 
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
}

void ledOrangeConfig(void) {
    ledInit(); 
	PORT_PCR_REG(PORTA_BASE_PTR, LED_ORANGE_PORTA_BIT) =
			PORT_PCR_MUX(PORT_PCR_MUX_GPIO);
	PTA_BASE_PTR->PDDR |= 1<<LED_ORANGE_PORTA_BIT;
}

void ledYellowConfig(void) {
    ledInit(); 
	PORT_PCR_REG(PORTA_BASE_PTR, LED_YELLOW_PORTA_BIT) =
			PORT_PCR_MUX(PORT_PCR_MUX_GPIO);
	PTA_BASE_PTR->PDDR |= 1<<LED_YELLOW_PORTA_BIT;
}

void ledGreenConfig(void) {
    ledInit(); 
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORT_PCR_REG(PORTA_BASE_PTR, LED_GREEN_PORTA_BIT) =
			PORT_PCR_MUX(PORT_PCR_MUX_GPIO);
	PTA_BASE_PTR->PDDR |= 1<<LED_GREEN_PORTA_BIT;
}

void ledBlueConfig(void) {
    ledInit(); 
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORT_PCR_REG(PORTA_BASE_PTR, LED_BLUE_PORTA_BIT) =
			PORT_PCR_MUX(PORT_PCR_MUX_GPIO);
	PTA_BASE_PTR->PDDR |= 1<<LED_BLUE_PORTA_BIT;
}

void ledOrangeOff(void) {
	PTA_BASE_PTR->PSOR = 1<<LED_ORANGE_PORTA_BIT;
}

void ledYellowOff(void) {
	PTA_BASE_PTR->PSOR = 1<<LED_YELLOW_PORTA_BIT;
}

void ledGreenOff(void) {
	PTA_BASE_PTR->PSOR = 1<<LED_GREEN_PORTA_BIT;
}

void ledBlueOff(void) {
	PTA_BASE_PTR->PSOR = 1<<LED_BLUE_PORTA_BIT;
}

void ledOrangeOn(void) {
	PTA_BASE_PTR->PCOR = 1<<LED_ORANGE_PORTA_BIT;
}

void ledYellowOn(void) {
	PTA_BASE_PTR->PCOR = 1<<LED_YELLOW_PORTA_BIT;
}

void ledGreenOn(void) {
	PTA_BASE_PTR->PCOR = 1<<LED_GREEN_PORTA_BIT;
}

void ledBlueOn(void) {
	PTA_BASE_PTR->PCOR = 1<<LED_BLUE_PORTA_BIT;
}

void ledOrangeWrite(int ch){
    printf("ledOrangeWrite ch = %d\n", ch);
    ch == 0? ledOrangeOn(): ledOrangeOff(); 
}
void ledYellowWrite(int ch){
    ch == 0? ledYellowOn(): ledYellowOff(); 
}
void ledGreenWrite(int ch){
    ch == 0? ledGreenOn(): ledGreenOff(); 
}
void ledBlueWrite(int ch){
    ch == 0? ledBlueOn(): ledBlueOff(); 
}

led_t leds[NUM_OF_LEDS] = { 
    {ledOrangeConfig, ledOrangeWrite}, 
    {ledYellowConfig, ledYellowWrite}, 
    {ledGreenConfig, ledGreenWrite}, 
    {ledBlueConfig, ledBlueWrite}, 
};


int ledinit(void * minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    leds[fd].init(); 
    return 0;
}

int ledwrite(int ch, void *minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    printf("ledwrite ch = %d\n", ch);
    leds[fd].write(ch); 
    return 0; 
}
