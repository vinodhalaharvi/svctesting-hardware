#include <stdio.h>
#include "mymalloc.h"
#include "file.h"
#include "stringutils.h"
#include <stdint.h>
#include "common.h"
#define MAX_FS_ENTRIES 1000

static  file_t * filesystem[MAX_FS_ENTRIES]; 

void allocblock(node_t *node){ 
    node->data = (void *) mymalloc(BLKSIZE); 
    memoryset(node->data, '\0', BLKSIZE); 
    node->next = NULL; 
    node->prev = NULL; 
}

file_t * newfile(){ 
    file_t * file; 
    file = (file_t *) mymalloc(sizeof(file_t)); 
    file->size = 0;
    file->offset = 0;
    myassert(file != NULL, "", "file != NULL"); 
    file->node = (node_t *) mymalloc(sizeof(node_t)); 
    allocblock(file->node); 
    return file; 
}

file_t * getfile(void * minor_num){ 
    unsigned index = (unsigned) (unsigned) minor_num; 
    myassert(index <= MAX_FS_ENTRIES, "", "index <= MAX_FS_ENTRIES"); 
    return filesystem[index]; 
}

int filewrite(int ch, void * minor_num){
    file_t * file = getfile(minor_num); 
    node_t *node = file->node; 
    myassert(node != NULL, "", "node != NULL"); 
    unsigned size = file->size; 
    unsigned blkno = size / BLKSIZE; 
    unsigned blkoffset = size % BLKSIZE; 
    unsigned i; 
    for (i = 0; i < blkno; ++i) {
        node = node->next; 
    }
    if (blkoffset == BLKSIZE){ 
        allocblock(node->next);
        node->next->prev = node; 
        node = node->next;
        blkoffset = 0; 
    }
    ((char *) node->data)[blkoffset++] = ch; 
    file->size++; 
    return 0; 
}


unsigned isfileexists(const char * filepath){ 
    unsigned i; 
    for (i = 0; i < MAX_FS_ENTRIES; ++i) {
        //assert(i <= MAX_FS_ENTRIES); 
        myassert(i <= MAX_FS_ENTRIES, "", "i <= MAX_FS_ENTRIES"); 
        if (filesystem[i] 
                && strcompare(filesystem[i]->filename, filepath) == 0){ 
            return true; 
        }
    }
    return false; 
}


//int fseek(FILE *stream, long offset, int whence);
void fileseek(void *minor_num, unsigned offset){
    file_t * file = getfile(minor_num); 
    file->offset = offset; 
}

int fileread(void *minor_num){
    file_t * file = getfile(minor_num); 
    myassert(file != NULL, "", "file != NULL"); 
    node_t *node = file->node; 
    myassert(node != NULL, "", "node != NULL"); 
    if (file->offset == file->size){ 
        return EOF; 
    }
    unsigned size = file->offset; 
    unsigned blkno = size / BLKSIZE; 
    unsigned blkoffset = size % BLKSIZE; 
    unsigned i; 
    for (i = 0; i < blkno; ++i) {
        node = node->next; 
    }
    if (blkoffset == BLKSIZE){ 
        allocblock(node->next); 
        node->next->prev = node; 
        node = node->next;
        blkoffset = 0; 
    }
    int ch = ((char *) node->data)[blkoffset]; 
    file->offset++; 
    return ch;
}

void ls(){
    unsigned i; 
    for (i = 0; i < MAX_FS_ENTRIES; ++i) {
        myassert(i <= MAX_FS_ENTRIES, "", "index <= MAX_FS_ENTRIES"); 
        if (filesystem[i] && filesystem[i]->filename){ 
            printf("%s\n", filesystem[i]->filename);
        }
    }
    printf("\n");
}

int fileinit(void * minor_num) { 
    file_t * file = getfile(minor_num); 
    myassert(file != NULL, "", "file != NULL"); 
    return 0;
}


int filerelease(void * minor_num){ 
    file_t * file = getfile(minor_num); 
    myassert(file != NULL, "", "file != NULL"); 
    return 0;
}

int get_file_inode(const char * filepath){ 
    unsigned i; 
    for (i = 0; i < MAX_FS_ENTRIES; ++i) {
        if (filesystem[i] && 
                strcompare(filesystem[i]->filename, filepath) == 0){ 
            return i; 
        }
    } 
    return -1; 
}

void create_file(const char * filename){
    unsigned i; 
    for (i = 0; i < MAX_FS_ENTRIES; ++i) {
        myassert(i <= MAX_FS_ENTRIES, "", "index <= MAX_FS_ENTRIES"); 
        if (!filesystem[i]){
            filesystem[i] = newfile(); 
            filesystem[i]->filename = strduplicate(filename); 
            return; 
        } 
    }
}


/*void free_file_memory(node_t * node){
    myassert(node != NULL, "", "node != NULL"); 
    node_t * temp; 
    while(node){ 
        myfree(node->data); 
        temp = node->next; 
        node = node->next ; 
        myfree(temp); 
    }
}*/

void free_file_memory(node_t * node){
    myassert(node != NULL, "", "node != NULL"); 
    while(node){ 
        myfree(node->data); 
        node = node->next ; 
    }
}


void delete_file(const char * filename){
    unsigned i; 
    for (i = 0; i < MAX_FS_ENTRIES; ++i) {
        myassert(i <= MAX_FS_ENTRIES, "", "index <= MAX_FS_ENTRIES"); 
        if (filesystem[i] 
                && strcompare(filesystem[i]->filename, filename) == 0){ 
            unsigned temp = get_file_inode(filename); 
            file_t * file = getfile((void *) (unsigned) temp); 
            free_file_memory(file->node);
            myfree(file);
            filesystem[i] = NULL; 
            return; 
        }
    }
    printf("File %s does not exist", filename); 
}
