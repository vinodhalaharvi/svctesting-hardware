#include "common.h"
#include "io.h"
#include <stdio.h>
unsigned mystdin; 
unsigned mystdout; 
void write_string(const char *p, unsigned mystdout) {
    while(*p) {
        mywrite(*p++, mystdout);
    }
}

void myassert(unsigned status, 
        const char *actual, const char *expected){ 
    if (status == 0){ 
        /*printf("Assertion Error: \nExpected: %s Found: %s\n", 
                expected, actual);*/
        char print_string[1000]; 
        sprintf(print_string, "Assertion Error: \nExpected: %s\n", expected);
        write_string(print_string, mystdout); 
    } 
}
