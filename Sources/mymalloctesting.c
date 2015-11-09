#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include "mymalloc.h"
#include <stdint.h>
#include "stringutils.h"
#define MAX_COUNT 10 
#define MAX_STRING_SIZE 10
#define MAX_STRING_LARGE_SIZE 1000


//test string and integer pointer
void teststringandint(){ 
    char print_string[1000]; 
    char * string1; 
    char * string2; 
    unsigned * int2; 
    char * string3; 
    sprintf(print_string, "%s\n", "********************");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "TEST STRING ALLOCATION");
    write_string(print_string, mystdout); 
    string1 = ( char * ) mymalloc(MAX_STRING_SIZE); 
    string2 = ( char * ) mymalloc(MAX_STRING_SIZE); 
    int2 = (unsigned *) mymalloc(sizeof(unsigned));  
    string3 = ( char * ) mymalloc(MAX_STRING_SIZE); 
    strcopy(string1, "one"); 
    assert(!strcompare(string1, "one")); 
    strcopy(string2, "two"); 
    assert(!strcompare(string2, "two")); 
    strcopy(string3, "three"); 
    assert(!strcompare(string3, "three")); 
    *int2 = 10;  
    assert(*int2 == 10); 
    sprintf(print_string, "%p is address of: %s\n", (void *)string1, string1);
    write_string(print_string, mystdout); 
    sprintf(print_string, "%p is address of: %s\n", (void *)string2, string2);
    write_string(print_string, mystdout); 
    sprintf(print_string, "%p is address of: %s\n", (void *)string3, string3);
    write_string(print_string, mystdout); 
    sprintf(print_string, "%p is address of: %d\n", (void *)int2, *int2);
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "Memory map after allocation");
    write_string(print_string, mystdout); 
    memorymap(); 
    sprintf(print_string, "Memory map after freeing string %s\n", string1);
    write_string(print_string, mystdout); 
    myfree(string1); 
    memorymap();  
    
    sprintf(print_string, "Memory map after freeing string %s\n", string2);
    write_string(print_string, mystdout); 
    myfree(string2); 
    memorymap(); 

    sprintf(print_string, "Memory map after freeing string %s\n", string3);
    write_string(print_string, mystdout); 
    myfree(string3); 
    memorymap(); 

    sprintf(print_string, "Memory map after freeing int %d\n", *int2);
    write_string(print_string, mystdout); 
    myfree(int2); 
    memorymap(); 
}


//simple testing for allocating and
//deallocating memory
void testfree(){ 
    char * string1, *string2, *string3; 
    sprintf(print_string, "%s\n", "********************");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "TEST FREE");
    write_string(print_string, mystdout); 
    string1 = (char * ) mymalloc(MAX_STRING_SIZE); 
    string2 = (char * ) mymalloc(MAX_STRING_SIZE); 
    string3 = (char * ) mymalloc(MAX_STRING_SIZE); 
    sprintf(print_string, "%s\n", "");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "Memory map after allocation");
    write_string(print_string, mystdout); 
    memorymap(); 
    strcopy(string1, "hello"); 
    assert(!strcompare(string1, "hello")); 
    strcopy(string2, "world"); 
    assert(!strcompare(string2, "world")); 
    strcopy(string3, "!"); 
    assert(!strcompare(string3, "!")); 
    sprintf(print_string, "Memory map after freeing string %s\n", string2);
    write_string(print_string, mystdout); 
    myfree(string2); memorymap(); 
    sprintf(print_string, "Memory map after freeing string %s\n", string1);
    write_string(print_string, mystdout); 
    myfree(string1); memorymap(); 
    sprintf(print_string, "Memory map after freeing string %s\n", string3);
    write_string(print_string, mystdout); 
    myfree(string3); memorymap(); 
    memorymap(); 
}



//test string allocation 
//and deallocation
void teststringallocation(){ 
    char * string1, *string2, *string3; 
    sprintf(print_string, "%s\n", "********************");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "TEST STRING ALLOCATION");
    write_string(print_string, mystdout); 
    string1 = (char * ) mymalloc(MAX_STRING_SIZE); 
    string2 = (char * ) mymalloc(MAX_STRING_SIZE); 
    string3 = (char * ) mymalloc(MAX_STRING_SIZE); 
    strcopy(string1, "hello"); 
    strcopy(string2, "world"); 
    strcopy(string3, "and"); 
    sprintf(print_string, "%p is the address of: %s\n", (void *)string1, string1);
    write_string(print_string, mystdout); 
    sprintf(print_string, "%p is the address of: %s\n", (void *)string2, string2);
    write_string(print_string, mystdout); 
    sprintf(print_string, "%p is the address of: %s\n", (void *)string3, string3);
    write_string(print_string, mystdout); 
    sprintf(print_string, "Memory map after freeing string %s\n", string2);
    write_string(print_string, mystdout); 
    myfree(string2); memorymap(); 
    sprintf(print_string, "Memory map after freeing string %s\n", string1);
    write_string(print_string, mystdout); 
    myfree(string1); memorymap(); 
    sprintf(print_string, "Memory map after freeing string %s\n", string3);
    write_string(print_string, mystdout); 
    myfree(string3); memorymap(); 
}

//test random alignment
/*void testrandomalign(){ 
    unsigned randomaddr;  
    unsigned i; 
    unsigned * temp; 
    sprintf(print_string, "%s\n", "********************");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "TEST RANDOMALIGN");
    write_string(print_string, mystdout); 
    sprintf(print_string, "Assigning Randomly 10 addresses with different sizes\n");
    write_string(print_string, mystdout); 
    sprintf(print_string, "and freeing them\n");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "Memory map before ..");
    write_string(print_string, mystdout); 
    memorymap(); 
    for (i = 0; i < 10; ++i) {
        //temp = (void *) mymalloc(sizeof(char) * MAX_STRING_SIZE); 
        randomaddr = ((unsigned) random() % MAX_COUNT) ; 
        temp = (void *) mymalloc(randomaddr); 
        assert((unsigned) temp % 8 == 0); 
        myfree(temp); 
    }
    sprintf(print_string, "%s\n", "");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "Memory map after ..");
    write_string(print_string, mystdout); 
    memorymap(); 
}


//test random allocation
void testrandom(){ 
    unsigned randomcount;  
    char * strings[MAX_COUNT]; 
    unsigned i; 
    char * temp; 
    sprintf(print_string, "%s\n", "********************");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "TEST RANDOM");
    write_string(print_string, mystdout); 
    randomcount = ((unsigned) random() % MAX_COUNT) ; 
    sprintf(print_string, 
            "Assigning Randomly %d addresses\n", randomcount);
    write_string(print_string, mystdout); 
    sprintf(print_string, "and freeing them\n");
    write_string(print_string, mystdout); 
    sprintf(print_string, "%s\n", "Memory map before ..");
    write_string(print_string, mystdout); 
    memorymap(); 
    for (i = 0; i < randomcount; ++i) {
        strings[i] = (char *) mymalloc(sizeof(char) * MAX_STRING_SIZE); 
        temp = (char *) mymalloc(sizeof(char) * MAX_STRING_SIZE); 
        sprintf(temp, "string%d", i); 
        write_string(print_string, mystdout); 
        strcopy(strings[i], temp); 
        assert(!strcompare(strings[i], temp));
        myfree(temp); 
        myfree(strings[i]); 
    }
    sprintf(print_string, "%s\n", "Memory map after ..");
    write_string(print_string, mystdout); 
    memorymap(); 
}*/

void verify_memory_allocation_mymemory_testing(){ 
    if (!is_memory_initialized()){ 
        initmemory(); 
    }
    sprintf(print_string, "%s\n", "MEMORY MAP BEFORE ANYTHING ..");
    write_string(print_string, mystdout); 
    memorymap(); 
    teststringallocation(); 
    teststringandint(); 
    testfree(); 
    //testrandomalign(); 
    //testrandom(); 
}
