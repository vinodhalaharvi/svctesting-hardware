#ifndef IO_H
#define IO_H value
#include "led.h"
#include "pushbutton.h"
#include "file.h"
#define MAX_DEVICES 100
#define MAX_FILE_DESCRIPTORS 1000
#define PREDEFINED_DEVICE_MAP 13

typedef struct _fdtable_t {
    int major_num; 
    int minor_num; 
} fdtable_t;

typedef struct _stream_t {
    int minorno; 
    int majorno; 
} stream_t;

typedef enum { LED, PUSHBUTTON, POTENTIOMETER, CAPACITIVEPAD, THERMISTOR, LCDC, UART, _FILE } major_device; 
typedef enum { LED_ORANGE, LED_YELLOW, LED_GREEN, LED_BLUE} led_minor_device;  
typedef enum { PUSHBUTTON_SW1, PUSHBUTTON_SW2 } pushbutton_minor_device;
typedef enum { POTENTIOMETER1} potentiometer_minor_device;
typedef enum { CAPACITIVEPAD1 , CAPACITIVEPAD2 , CAPACITIVEPAD3 , CAPACITIVEPAD4 } capacitivepad_minor_device; 
typedef enum { THERMISTOR1} thermistor_minor_device; 
typedef enum { LCDC1} lcdc_minor_device; 
typedef enum { UART1} uart_minor_device; 


typedef struct _filepath_to_device_t {
    const char * filepath; 
    unsigned major_num; 
    unsigned minor_num; 
} filepath_to_device_t;

int get_minor_num(const char * filepath); 
int get_major_num(const char * filepath); 
int create_fd(int major_num, int minor_num); 
int get_fd(int major_num, int minor_num); 
int myopen(const char * filepath, unsigned mode); 
int myclose(int fd); 
int mywrite(int fd, int ch); 
int isdevice(int major_num); 
int isfile(int major_num); 
int myread(int fd); 
void assert_memory_is_initialized(); 
void verify_device_independent_file_operations(); 
void init_fdtable(); 
void cat(unsigned fd); 
#endif


