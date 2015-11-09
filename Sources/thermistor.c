/* Source copied from CSCIE-92 class sample code */
#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>
#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "thermistordriver.h"
#include "thermistor.h"
typedef unsigned long uintptr_t; 

thermistor_t thermistors[NUM_OF_THERMISTORS] = { 
    {thermistor_driver_init, thermistor_driver_read}
};

int thermistor_init(void * minor_num){ 
    int fd = (int) (uintptr_t) minor_num; 
    thermistors[fd].init(); 
    return 0;
}

int thermistor_read(void *minor_num){ 
    int fd = (int) (uintptr_t) minor_num; 
    thermistors[fd].read(); 
    return 0; 
}

