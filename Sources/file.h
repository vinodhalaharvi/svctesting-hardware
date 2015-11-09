#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H 1
#define BLKSIZE 128
#define FILE_READONLY 1
#define FILE_READWRITE 3 
#define FILE_CREATE 5
#define FILE_APPEND 7 

typedef struct _node_t {
    void * data; 
    struct _node_t *prev; 
    struct _node_t *next; 
} node_t;

typedef struct _file_t {
    char * filename; 
    unsigned size; 
    unsigned offset;
    node_t *node; 
} file_t;

unsigned isfileexists(const char * filepath); 
void allocblock(node_t *node); 
int get_file_inode(const char * filepath); 
file_t * newfile(); 
file_t * getfile(void * minor_num); 
void free_file_memory(node_t * node);

//public interface
void ls(); 
int fileinit (void * minorno); 
int filerelease (void * minorno); 
int fileread (void * minorno); 
int filewrite (int ch, void * minorno); 
void fileseek(void *minorno, unsigned offset); 
void create_file(const char * filename);
void delete_file(const char * filename);
#endif
