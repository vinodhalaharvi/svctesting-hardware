/* Source copied from CSCIE-92 class sample code */

#ifndef _CAPACITIVEPAD_H
#define _CAPACITIVEPAD_H
#define NUM_OF_CAPACITIVEPADS 4 
typedef struct _capacitivepad_t {
    void (*init)(void); 
    void (*calibrate)(void); 
    int  (*read)(int); 
} capacitivepad_t;

int capacitivepad_init(void *minor_num); 
void capacitivepad_calibrate(void *minor_num);  
int capacitivepad_read(void *minor_num); 
#endif

