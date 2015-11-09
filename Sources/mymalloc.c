#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mymalloc.h"
#include "stringutils.h"
#include "common.h"
#include "sdram.h"

#define MEMORY_DATA_PADDING 10
#define ALIGN_SIZE 7

static char * start; 
static char * memory_end; 

unsigned align(unsigned value){ 
    unsigned result; 
    result =   (value + ALIGN_SIZE) & (~ALIGN_SIZE); 
    assert(result % 8 == 0);
    return result; 
}

int getcurrentprocessid(){ 
    return 0; 
}

void assert_memory_is_initialized(){ 
    assert(start); 
}

unsigned is_memory_initialized(){ 
    return start != NULL;
}

void reinitalize_memory(){ 
    free(start); 
    initmemory(); 
}

unsigned initmemory(){ 
    initmemory_sdram(); 
    return 1; 
}

unsigned initmemory_ram(){ 
    start = (char *) malloc(MEMORY_SIZE); 
    memory_end = start + MEMORY_SIZE; 
    ((mymalloc_t *) start)->size = MEMORY_SIZE; 
    ((mymalloc_t *) start)->free = 1; 
    ((mymalloc_t *) start)->pid = getcurrentprocessid(); 
    return 1; 
}

unsigned initmemory_sdram(){ 
    start = (char *) SDRAM_START; 
    memory_end = (char *) (SDRAM_START + SDRAM_SIZE); 
    ((mymalloc_t *) start)->size = SDRAM_SIZE; 
    ((mymalloc_t *) start)->free = 1; 
    ((mymalloc_t *) start)->pid = getcurrentprocessid(); 
    return 1; 
}

char * next(char *trav){ 
    assert(((mymalloc_t *)trav)->size); 
    return trav + ((mymalloc_t *) trav)->size; 
}

int hole(char * trav){ 
    return ((mymalloc_t *) trav)->free; 
}

void taken(char *node, unsigned size){ 
    assert(size); 
    ((mymalloc_t *) node)->size = size; 
    ((mymalloc_t *) node)->free = 0; 
}

unsigned sizeofnode(void * node){ 
    return((mymalloc_t *) node)->size; 
}

void * mymalloc(unsigned size){ 
    char * trav = start; 
    unsigned newsize; 
    void * data;
    myassert(size > 0 , "", "size"); 
    size = align(size + sizeof(mymalloc_t)); 
    //padding in case user overflows
    size += align(MEMORY_DATA_PADDING); 
    while(trav < memory_end){ 
        if (hole(trav) && sizeofnode(trav) >= size){ 
            newsize = ((mymalloc_t *) trav)->size - size; 
            ((mymalloc_t *) trav)->size = newsize; 
            taken(trav + newsize, size); 
            //return (void *) ((mymalloc_t *) (trav + newsize))->data; 
            data =  (void *) ((mymalloc_t *) (trav + newsize))->data; 
            memoryset(data, '\0', size - sizeof(mymalloc_t)); 
            return data; 
        }
        trav = next(trav);
    }
    return NULL; 
}

void printnode(char *trav){ 
    char print_string[1000]; 
    //sprintf(print_string, "addr= %p ", (void *)trav);
    sprintf(print_string, "addr= %p ", ((mymalloc_t *) (trav))->data); 
    write_string(print_string); 
    sprintf(print_string, "size=%lu ", ((mymalloc_t *) trav)->size - sizeof(mymalloc_t));
    write_string(print_string); 
    //sprintf(print_string, "size=%u ", ((mymalloc_t *) trav)->size);
    sprintf(print_string, "status=%s \n", 
            ((mymalloc_t *) trav)->free == 1? "free": "taken");
    write_string(print_string); 
}

void merge(char * trav){ 
    if (hole(trav) && hole(next(trav))){ 
        ((mymalloc_t *) trav)->size += 
            ((mymalloc_t *) next(trav))->size; 
    }
}

void myfree(void *addr){ 
    char * trav = start; 
    while(trav < memory_end){ 
        //merge(trav); 
        if ((void *)((mymalloc_t *) trav)->data == addr) { 
            ((mymalloc_t *) trav)->free = 1; 
            return; 
        }
        trav = next(trav);
    }
}


void memorymap(){ 
    char print_string[1000]; 
    return ; 
    assert(start);
    char * trav = start; 
    while(trav < memory_end){ 
        printnode(trav); 
        assert(((mymalloc_t *) trav)->size); 
        trav = trav + ((mymalloc_t *) trav)->size; 
    }
    sprintf(print_string, "\n");
    write_string(print_string); 
}

void defragment_memory(unsigned iterations){ 
    unsigned i;
    for (i = 0; i < iterations; ++i) {
        myfree(NULL); 
    }
}


void verify_memory_allocation() {
    char * string1, *string2, *string3; 
    initmemory(); 
    memorymap(); 

    string1 = (char *) mymalloc(strlen("hello") + 1); 
    strcpy(string1, "hello"); 
    assert(!strcmp(string1, "hello")); 
    memorymap(); 

    string2 = (char *) mymalloc(strlen("world!") + 1); 
    strcpy(string2, "world!"); 
    assert(!strcmp(string2, "world!")); 
    memorymap(); 

    string3 = (char *) mymalloc(strlen("Something else") + 1); 
    strcpy(string3, "Something else"); 
    assert(!strcmp(string3, "Something else")); 
    myfree(string3); 

    memorymap(); 
    defragment_memory(4); 
    memorymap(); 
}
