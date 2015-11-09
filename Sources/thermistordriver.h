#ifndef _THERMISTORDRIVER_H
#define _THERMISTORDRIVER_H 
#include <stdint.h>

#define FALSE 0
#define TRUE 1

#define ADC_CHANNEL_THERMISTOR   	0x14
#define ADC_CHANNEL_TEMPERATURE_SENSOR  0x1A

#define ADC_CFG1_MODE_8_9_BIT       0x0
#define ADC_CFG1_MODE_12_13_BIT     0x1
#define ADC_CFG1_MODE_10_11_BIT     0x2
#define ADC_CFG1_MODE_16_BIT        0x3
#define ADC_SC3_AVGS_32_SAMPLES     0x3
void thermistor_driver_init(void); 
unsigned int thermistor_driver_read(); 
#endif
