#ifndef _MAP_H
#define _MAP_H value
//Author: Vinod Halaharvi
#include <stdint.h>
#include "common.h"
typedef const char * key_type; 
typedef const char * value_type; 
#define MAX_LIST_SIZE 100

typedef struct node_type {
    key_type key; 
    value_type value; 
    struct node_type * next; 
    struct node_type * prev; 
    unsigned size; 
} node_type;

value_type get(node_type * node, key_type key); 
node_type *put(node_type * node, key_type key, value_type value); 
void delete_key(node_type **head, key_type key); 
void freemapnode(node_type * node); 

/* misc functions */
void print(node_type * environ);
boolean contains(node_type * node, key_type key); 
boolean match(key_type key, key_type otherkey); 
#endif
