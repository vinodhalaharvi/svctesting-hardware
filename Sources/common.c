#include "common.h"
#include <stdio.h>
void myassert(unsigned status, 
        const char *actual, const char *expected){ 
    if (status == 0){ 
        /*printf("Assertion Error: \nExpected: %s Found: %s\n", 
                expected, actual);*/
        printf("Assertion Error: \nExpected: %s\n", expected);
    } 
}
