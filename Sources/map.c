#include <stdio.h>
#include "stringutils.h"
#include "map.h"
#include "mymalloc.h"

//Author: Vinod Halaharvi
//Very rudimentary doubly linked list 
//to keep track of environment variables
int verify_map() {
    node_type * environ = NULL; 
    //map.c testing..
    environ = put(environ, "key1", "value1");
    environ = put(environ, "key2", "value2");
    environ = put(environ, "key3", "value3");
    //assert(contains(environ, "key1") == true); 
    //assert(contains(environ, "key2") == true); 
    //assert(contains(environ, "key3") == true); 
    delete_key(&environ, "key2"); 
    //assert(contains(environ, "key2") == false); 
    print(environ); 
    return 0; 
}

//helper function to print the list
void print(node_type * environ){
    char print_string[1000]; 
    while(environ){
        sprintf(print_string, "%s = %s\n", environ->key, environ->value);
        write_string(print_string, mystdout); 
        environ = environ->next;
    }
}

//get the value for a given key
value_type get(node_type * node, key_type key){
    while(node){
        if (match(node->key, key)){ 
            return node->value; 
        }
        node = node->next;
    }
    return NULL; 
}

//delete from the list
//many edge cases to consider
void delete_key(node_type **head, key_type key){
    node_type * node = *head; 
    while(node){
        if (match(node->key, key)){ 
            //delete the entire list if there is only one node
            if (node->prev == NULL && node->next == NULL){ 
                //freemapnode(node); 
                *head = NULL; 
                return;
            }
            //delete intermediate node
            if (node->prev && node->next){ 
                node->prev->next = node->next; 
                node->next->prev = node->prev; 
                //freemapnode(node); 
                return; 
            }
            //delete last node
            if(node->next == NULL) { 
                node->prev->next = NULL; 
                //freemapnode(node); 
                return; 
            }

            //delete first node
            if(node->prev == NULL) { 
                *head = node->next; 
                //freemapnode(node); 
                return; 
            }
        }
        node = node->next; 
    }
    return;
}


//put the key, value pair in this list
node_type * put(node_type * node, key_type key, value_type value){
    node_type * temp = (node_type *) mymalloc(sizeof(node_type)); 
    memoryset(temp, '\0', sizeof(node_type)); 
    temp->key = key; 
    temp->value = value; 
    temp->next = NULL; 
    temp->prev = NULL; 
    if (node){ 
        temp->next = node; 
        node->prev = temp; 
    } else { 
        temp->next = NULL; 
        temp->prev = NULL; 
    }
    return temp; 
}

//simple helper function for string equals
boolean match(key_type key, key_type otherkey) { 
    return (strcompare(key, otherkey) == 0)? 1 : 0; 
}
 
//check if list contains the key
boolean contains(node_type * node, key_type key){
    while(node){
        if (match(node->key, key)){ 
            return true; 
        }
        node = node->next;
    }
    return false; 
}
