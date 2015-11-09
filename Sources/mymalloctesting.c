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
    char * string1; 
    char * string2; 
    unsigned * int2; 
    char * string3; 
    printf("%s\n", "********************");
    printf("%s\n", "TEST STRING ALLOCATION");
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
    printf("%p is address of: %s\n", (void *)string1, string1);
    printf("%p is address of: %s\n", (void *)string2, string2);
    printf("%p is address of: %s\n", (void *)string3, string3);
    printf("%p is address of: %d\n", (void *)int2, *int2);
    printf("%s\n", "");
    printf("%s\n", "Memory map after allocation");
    memorymap(); 
    printf("Memory map after freeing string %s\n", string1);
    myfree(string1); 
    memorymap();  
    
    printf("Memory map after freeing string %s\n", string2);
    myfree(string2); 
    memorymap(); 

    printf("Memory map after freeing string %s\n", string3);
    myfree(string3); 
    memorymap(); 

    printf("Memory map after freeing int %d\n", *int2);
    myfree(int2); 
    memorymap(); 
}


//simple testing for allocating and
//deallocating memory
void testfree(){ 
    char * string1, *string2, *string3; 
    printf("%s\n", "********************");
    printf("%s\n", "TEST FREE");
    string1 = (char * ) mymalloc(MAX_STRING_SIZE); 
    string2 = (char * ) mymalloc(MAX_STRING_SIZE); 
    string3 = (char * ) mymalloc(MAX_STRING_SIZE); 
    printf("%s\n", "");
    printf("%s\n", "Memory map after allocation");
    memorymap(); 
    strcopy(string1, "hello"); 
    assert(!strcompare(string1, "hello")); 
    strcopy(string2, "world"); 
    assert(!strcompare(string2, "world")); 
    strcopy(string3, "!"); 
    assert(!strcompare(string3, "!")); 
    printf("Memory map after freeing string %s\n", string2);
    myfree(string2); memorymap(); 
    printf("Memory map after freeing string %s\n", string1);
    myfree(string1); memorymap(); 
    printf("Memory map after freeing string %s\n", string3);
    myfree(string3); memorymap(); 
    memorymap(); 
}



//test string allocation 
//and deallocation
void teststringallocation(){ 
    char * string1, *string2, *string3; 
    printf("%s\n", "********************");
    printf("%s\n", "TEST STRING ALLOCATION");
    string1 = (char * ) mymalloc(MAX_STRING_SIZE); 
    string2 = (char * ) mymalloc(MAX_STRING_SIZE); 
    string3 = (char * ) mymalloc(MAX_STRING_SIZE); 
    strcopy(string1, "hello"); 
    strcopy(string2, "world"); 
    strcopy(string3, "and"); 
    printf("%p is the address of: %s\n", (void *)string1, string1);
    printf("%p is the address of: %s\n", (void *)string2, string2);
    printf("%p is the address of: %s\n", (void *)string3, string3);
    printf("Memory map after freeing string %s\n", string2);
    myfree(string2); memorymap(); 
    printf("Memory map after freeing string %s\n", string1);
    myfree(string1); memorymap(); 
    printf("Memory map after freeing string %s\n", string3);
    myfree(string3); memorymap(); 
}

//test random alignment
/*void testrandomalign(){ 
    unsigned randomaddr;  
    unsigned i; 
    unsigned * temp; 
    printf("%s\n", "********************");
    printf("%s\n", "TEST RANDOMALIGN");
    printf("Assigning Randomly 10 addresses with different sizes\n");
    printf("and freeing them\n");
    printf("%s\n", "Memory map before ..");
    memorymap(); 
    for (i = 0; i < 10; ++i) {
        //temp = (void *) mymalloc(sizeof(char) * MAX_STRING_SIZE); 
        randomaddr = ((unsigned) random() % MAX_COUNT) ; 
        temp = (void *) mymalloc(randomaddr); 
        assert((unsigned) temp % 8 == 0); 
        myfree(temp); 
    }
    printf("%s\n", "");
    printf("%s\n", "Memory map after ..");
    memorymap(); 
}


//test random allocation
void testrandom(){ 
    unsigned randomcount;  
    char * strings[MAX_COUNT]; 
    unsigned i; 
    char * temp; 
    printf("%s\n", "********************");
    printf("%s\n", "TEST RANDOM");
    randomcount = ((unsigned) random() % MAX_COUNT) ; 
    printf(
            "Assigning Randomly %d addresses\n", randomcount);
    printf("and freeing them\n");
    printf("%s\n", "Memory map before ..");
    memorymap(); 
    for (i = 0; i < randomcount; ++i) {
        strings[i] = (char *) mymalloc(sizeof(char) * MAX_STRING_SIZE); 
        temp = (char *) mymalloc(sizeof(char) * MAX_STRING_SIZE); 
        sprintf(temp, "string%d", i); 
        strcopy(strings[i], temp); 
        assert(!strcompare(strings[i], temp));
        myfree(temp); 
        myfree(strings[i]); 
    }
    printf("%s\n", "Memory map after ..");
    memorymap(); 
}*/

void verify_memory_allocation_mymemory_testing(){ 
    if (!is_memory_initialized()){ 
        initmemory(); 
    }
    printf("%s\n", "MEMORY MAP BEFORE ANYTHING ..");
    memorymap(); 
    teststringallocation(); 
    teststringandint(); 
    testfree(); 
    //testrandomalign(); 
    //testrandom(); 
}
