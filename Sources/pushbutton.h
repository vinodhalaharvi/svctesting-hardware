#ifndef _PUSHBUTTON_H
#define _PUSHBUTTON_H value
#define NUM_OF_PUSHBUTTONS 2

typedef struct _pushbutton_t {
    void (*init)(void); 
    int (*read)(void); 
} pushbutton_t;

int pushbutton_init(void * minor_num); 
int pushbutton_read(void * minor_num); 
#endif
