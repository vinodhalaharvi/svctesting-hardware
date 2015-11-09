/* Source copied from CSCIE-92 class sample code */

#ifndef _THERMISTOR_H
#define _THERMISTOR_H
#define NUM_OF_THERMISTORS 1
#include <stdint.h>

typedef struct _thermistor_t {
    void (*init)(void); 
    unsigned int (*read)(); 
} thermistor_t;

int thermistor_init(void *minorno); 
int thermistor_read(void *minorno);
#endif
