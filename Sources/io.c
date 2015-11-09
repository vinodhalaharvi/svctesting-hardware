#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "mymalloc.h"
#include "io.h"
#include "file.h"
#include "stringutils.h"
#include "pushbutton.h"
#include "capacitivepads.h"
#include "thermistor.h"
#include "potentiometer.h"
#include "uart.h"
#include "lcdc.h"
#include "led.h"
typedef unsigned long uintptr_t; 

//fdtable_t fdtable[MAX_FILE_DESCRIPTORS]; 
static filepath_to_device_t filepath_to_major_minor[PREDEFINED_DEVICE_MAP] = { 
    {"/dev/led/orange", LED, LED_ORANGE}, 
    {"/dev/led/yellow", LED, LED_YELLOW}, 
    {"/dev/led/green", LED, LED_GREEN}, 
    {"/dev/led/blue", LED, LED_BLUE}, 
    {"/dev/pushbutton/1", PUSHBUTTON, PUSHBUTTON_SW1}, 
    {"/dev/pushbutton/2", PUSHBUTTON, PUSHBUTTON_SW2}, 
    {"/dev/capacitivepad/1", CAPACITIVEPAD,CAPACITIVEPAD1}, 
    {"/dev/capacitivepad/2",  CAPACITIVEPAD, CAPACITIVEPAD2},  
    {"/dev/capacitivepad/3",  CAPACITIVEPAD, CAPACITIVEPAD3},  
    {"/dev/capacitivepad/4",  CAPACITIVEPAD, CAPACITIVEPAD4},  
    {"/dev/uart/1", UART, UART1},
    {"/dev/lcdc/1", LCDC, LCDC1}, 
    {"/dev/thermistor/1",THERMISTOR,THERMISTOR1}, 
}; 

static fdtable_t fdtable[MAX_FILE_DESCRIPTORS]; 

void init_led_fdtable(){ 
    unsigned i;
    for (i = 0; i < NUM_OF_LEDS; ++i) {
        create_fd(LED, i); 
    }
}

void init_pushbutton_fdtable(){ 
    unsigned i;
    for (i = 0; i < NUM_OF_PUSHBUTTONS; ++i) {
        create_fd(PUSHBUTTON, i); 
    }
}


void init_lcdc_fdtable(){ 
    unsigned i;
    for (i = 0; i < NUM_OF_LCDCS; ++i) {
        create_fd(LCDC, i); 
    }
}

void init_uart_fdtable(){ 
    unsigned i;
    for (i = 0; i < NUM_OF_UARTS; ++i) {
        create_fd(UART, i); 
    }
}

void init_capacitive_fdtable(){ 
    unsigned i;
    for (i = 0; i < NUM_OF_CAPACITIVEPADS; ++i) {
        create_fd(CAPACITIVEPAD, i); 
    }
}

void init_potentiometer_fdtable(){ 
    unsigned i;
    for (i = 0; i < NUM_OF_POTENTIOMETERS; ++i) {
        create_fd(POTENTIOMETER, i); 
    }
}

void init_fdtable(){ 
    unsigned i; 
    init_led_fdtable(); 
    init_pushbutton_fdtable(); 
    for (i = 0; i < MAX_FILE_DESCRIPTORS; ++i) {
        fdtable[i].major_num = -1; 
        fdtable[i].minor_num = -1; 
    }
}

static struct device {
    int (*init)(void * minor_num); 
    int (*release)(void * minor_num); 
    int (*read)(void * minor_num); 
    int (*write)(int ch, void *minor_num); 
} devices[MAX_DEVICES] = {
    {led_init, NULL, NULL, led_write}, 
    {pushbutton_init, NULL, pushbutton_read, NULL}, 
    {potentiometer_init, NULL, potentiometer_read, NULL}, 
    {capacitivepad_init, NULL, capacitivepad_read, NULL}, 
    {thermistor_init, NULL, thermistor_read, NULL}, 
    {lcdc_init, NULL, NULL, lcdc_write}, 
    {uart_init, NULL, uart_read, uart_write}, 
    {fileinit, filerelease, fileread, filewrite} 
}; 

//static map
int isdevice(int major_num) { 
    return (major_num == LED) ||  (major_num == PUSHBUTTON); 
}

int isfile(int major_num){ 
    return !isdevice(major_num); 
}

int get_minor_num(const char * filepath){ 
    unsigned i; 
    for (i = 0; i < PREDEFINED_DEVICE_MAP; ++i) {
        if (strcompare(filepath, filepath_to_major_minor[i].filepath) == 0){ 
            return filepath_to_major_minor[i].minor_num; 
        }
    }
    return -1; 
}

int get_major_num(const char * filepath){ 
    if (strstr(filepath, "/dev/led")){ 
        return LED; 
    } else if (strstr(filepath, "/dev/pushbutton")){ 
        return PUSHBUTTON; 
    } else { 
        return _FILE; 
    }
}

int create_fd(int major_num, int minor_num){ 
    static unsigned fd; 
    unsigned i; 
    unsigned max_fd = PREDEFINED_DEVICE_MAP + NUM_OF_PUSHBUTTONS; 
    myassert(fd <= max_fd, "", "fd <= max_fd"); 
    for (i = 0; i < max_fd; ++i) {
        if(fdtable[i].major_num == -1){ 
            myassert(fdtable[i].minor_num == -1, "", "fdtable[i].minor_num == -1"); 
            fdtable[fd].major_num =  major_num; 
            fdtable[fd].minor_num = minor_num; 
            return fd; 
        }
    }
    return -1; 
}

int get_fd(int major_num, int minor_num){ 
    unsigned i; 
    for (i = 0; i < PREDEFINED_DEVICE_MAP + MAX_FILE_DESCRIPTORS; ++i) {
        if (fdtable[i].major_num == major_num &&
                fdtable[i].minor_num == minor_num){ 
            return i; 
        }
    }
    return -1;
}

//###################################################
//get major_num and minor_num
//get_fd or creatfd from major_num and minor_num
//return fd
int myopen(const char * filepath, unsigned mode){ 
    int major_num, minor_num; 
    int fd; 
    major_num = get_major_num(filepath); 
    minor_num = get_minor_num(filepath); 
    if (isdevice(major_num)){ 
        fd = get_fd(major_num, minor_num); 
        myassert(fd != -1, "", "fd != -1"); 
        return fd; 
    } else { 
        if (!isfileexists(filepath)){ 
            if (mode == FILE_CREATE){ 
                create_file(filepath); 
                minor_num = get_file_inode(filepath); 
                myassert(minor_num != -1, "", "minor_num != -1"); 
                devices[major_num].init((void *) (uintptr_t) minor_num); 
                fd = create_fd(major_num, minor_num); 
                return fd; 
            } 
        } else { 
            minor_num = get_file_inode(filepath); 
            fd = get_fd(major_num, minor_num); 
            myassert(fd != -1, "", "fd != -1"); 
            return fd; 
            //file does not exists
        } 
    }
    return -1; 
}

int myclose(int fd){ 
    int major_num; 
    int minor_num; 
    myassert(fd >= 0, "", "fd >= 0"); 
    myassert(fd <= MAX_FILE_DESCRIPTORS, "", "fd <= MAX_FILE_DESCRIPTORS"); 
    major_num = fdtable[fd].major_num; 
    minor_num = fdtable[fd].minor_num; 
    devices[major_num].release((void *) (uintptr_t) minor_num); 
    return 0;
}

int mywrite(int fd, int ch){ 
    int major_num; 
    int minor_num; 
    myassert(fd >= 0, "", "fd >= 0"); 
    myassert(fd <= (MAX_FILE_DESCRIPTORS + PREDEFINED_DEVICE_MAP), 
            "", "fd <= MAX_FILE_DESCRIPTORS + PREDEFINED_DEVICE_MAP"); 
    major_num = fdtable[fd].major_num; 
    minor_num = fdtable[fd].minor_num; 
    devices[major_num].write(ch, (void *) (uintptr_t) minor_num); 
    return 0; 
}

int myread(int fd){ 
    int major_num; 
    int minor_num; 
    int ch; 
    myassert(fd >= 0, "", "fd >= 0"); 
    myassert(fd <= MAX_FILE_DESCRIPTORS, "", "fd <= MAX_FILE_DESCRIPTORS"); 
    major_num = fdtable[fd].major_num; 
    minor_num = fdtable[fd].minor_num; 
    ch = devices[major_num].read((void *) (uintptr_t) minor_num); 
    return ch; 
}

void cat(unsigned fd){ 
    int  ch; 
    while((ch = myread(fd)) != EOF){ 
        fputc(ch, stdout); 
    }
}

void verify_device_independent_file_operations(){ 
    int fd; 
    int ch; 
    unsigned i; 
    const char * filename = "/tmp/test.txt"; 
    if (!is_memory_initialized()){ 
        initmemory(); 
    }
    init_fdtable(); 
    fd = myopen(filename, FILE_CREATE); 
    fd = myopen("/tmp/test1.txt", FILE_CREATE); 
    fd = myopen("/tmp/test2.txt", FILE_CREATE); 
    fd = myopen("/tmp/test3.txt", FILE_CREATE); 
    myassert(fd != -1, "", "fd != -1"); 
    i = 0; 
    const char * string = "hello world!"; 
    char * print_string = (char *) mymalloc(1000);  
    sprintf(print_string, "Writing string '%s %s' to the file\n", string, filename); 
    write_string(print_string, mystdout); 
    do {
        mywrite(fd, string[i]); 
    } while(string[i++]);
    print_string = (char *) mymalloc(1000);  
    sprintf(print_string, "Reading from file %s\n", filename);
    write_string(print_string, mystdout); 
    while((ch = myread(fd)) != EOF){ 
        fputc(ch, stdout); 
    }
    sprintf(print_string, "\n%s\n", "Files before ..");
    write_string(print_string, mystdout); 
    ls(); 
    delete_file(filename); 
    sprintf(print_string, "Files after deleting file %s:\n", filename);
    write_string(print_string, mystdout); 
    ls(); 
    sprintf(print_string, "\n");
    writ_string(print_string, mystdout); 
}
