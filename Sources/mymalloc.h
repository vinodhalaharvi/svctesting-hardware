#ifndef MYMALLOC_H
#define MYMALLOC_H 
#define MEMORY_SIZE 1024 * 10

typedef struct _mymalloc_t {
    unsigned size; 
    unsigned free; 
    unsigned pid;
    char * data[0]; 
} mymalloc_t;

int getcurrentprocessid(); 
unsigned initmemory(); 
void printnode(char *trav); 
void * mymalloc(unsigned size); 
void myfree(void *addr); 
void memorymap(); 
void assert_memory_is_initialized(); 
unsigned is_memory_initialized(); 
void reinitalize_memory(); 
unsigned initmemory_ram(); 
unsigned initmemory_sdram(); 
#endif
