/* Source copied from CSCIE-92 class sample code */
#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "lcdc.h"
#include "lcdcdriver.h"

lcdc_t lcdcs[NUM_OF_LCDCS] = { 
    {lcdc_driver_init, lcdc_driver_write}, 
};

int lcdc_init(void * minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    lcdcs[fd].init(); 
    return 0;
}

int lcdc_write(int ch, void *minor_num){ 
    int fd = (int) (unsigned) minor_num; 
    lcdcs[fd].write(ch); 
    return 0; 
}
