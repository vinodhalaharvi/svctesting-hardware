/* Source copied from CSCIE-92 class sample code */
#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "capacitivepadsdriver.h"
#include "capacitivepads.h"

capacitivepad_t capacitivepads[NUM_OF_CAPACITIVEPADS] = { 
    {TSI_Init, TSI_Calibrate, electrode_in}, 
    {TSI_Init, TSI_Calibrate, electrode_in}, 
    {TSI_Init, TSI_Calibrate, electrode_in}, 
    {TSI_Init, TSI_Calibrate, electrode_in} 
};

int capacitivepad_init(void * minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    capacitivepads[fd].init(); 
    return 0;
}

void capacitivepad_calibrate(void *minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    capacitivepads[fd].calibrate(); 
}

int capacitivepad_read(void *minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    capacitivepads[fd].read(fd); 
    return 0; 
}
