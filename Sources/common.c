#include "common.h"
#include <stdio.h>
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
