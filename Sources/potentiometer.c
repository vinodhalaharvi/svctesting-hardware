/* Source copied from CSCIE-92 class sample code */
#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>
#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "potentiometerdriver.h"
#include "potentiometer.h"

potentiometer_t potentiometers[NUM_OF_POTENTIOMETERS] = { 
    {potentiometer_deriver_init, potentiometer_driver_read}
};

int potentiometer_init(void * minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    potentiometers[fd].init(); 
    return 0;
}

int potentiometer_read(void *minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    //still have to fix this
    potentiometers[fd].read(); 
    return 0; 
}

int verify(void) {
   potentiometer_driver_init();
   while(TRUE) { 
      printf("pot: %4u\ttemp: %4u\n",
    		 potentiometer_driver_read(ADC_CHANNEL_POTENTIOMETER), 
    		 potentiometer_driver_read(ADC_CHANNEL_TEMPERATURE_SENSOR));
   }
   return 0;
}
