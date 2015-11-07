/* Source copied from CSCIE-92 class sample code */

#ifndef _POTENTIOMETER_H
#define _POTENTIOMETER_H
#define NUM_OF_POTENTIOMETERS 1
#include <stdint.h>

typedef struct _potentiometer_t {
    void (*init)(void); 
    unsigned int (*read)(uint8_t channel); 
} potentiometer_t;


void potentiometerInitAll(void);
int potentiometer_init(void *minorno); 
int potentiometer_read(void *minorno);
#endif
