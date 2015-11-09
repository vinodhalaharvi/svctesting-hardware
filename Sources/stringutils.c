#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "stringutils.h"
#include "common.h"

//Author: Vinod Halaharvi
//Hand rolled string functions
char * strcopy(char * dst, const char * src){ 
    unsigned i = 0; 
    while(src[i]){ 
        dst[i] = src[i]; 
        i++; 
    }
    dst[i] = '\0'; 
    return dst; 
}

unsigned strlength(const char * string){ 
    unsigned i = 0; 
    while(string[i++]); 
    return --i;
}


void memoryset(void *memory, char ch, unsigned len){ 
    unsigned i; 
    for (i = 0; i < len; ++i) {
        ((char *)memory)[i] = ch; 
    }
}


char * stralloc(unsigned len){ 
    char * temp = (char * ) mymalloc(len); 
    myassert(temp != NULL, "" , " temp null"); 
    unsigned i = 0; 
    for (i = 0; i < len; ++i) {
        temp[i] = '\0';
    }
    return temp; 
}


char * strduplicate(const char * src){ 
    char * temp; 
    temp = stralloc(strlength(src) + 1); 
    strcopy(temp, src); 
    return temp; 
}

char * strltrim(const char * src){ 
    char * temp; 
    const char *trav; 
    trav = src; 
    temp = stralloc(strlength(src) + 1); 
    while(*trav == ' ')
        trav++; 
    strcopy(temp, trav); 
    return temp; 
}


char * strrtrim(const char * src){ 
    char * temp, *trav; 
    temp = strduplicate(src); 
    trav = temp; 
    while(*trav++); --trav; --trav;
    while(*trav == ' ')
        --trav; 
    *(trav+1) = '\0'; 
    return temp; 
}

char * strlrtrim(const char * src){ 
    char * ltrimstr, *rtrimstr; 
    ltrimstr = strltrim(src); 
    rtrimstr = strrtrim(ltrimstr); 
    myfree(ltrimstr); 
    return rtrimstr; 
}


unsigned strcompare(const char * s1, const char * s2){ 
    unsigned i = 0; 
    if (strlength(s1) != strlength(s2))
        return 1; 
    while(s1[i]){ 
        if (s1[i] != s2[i]){ 
            return 1; 
        }
        i++; 
    }
    return 0; 
}


void verify_string_operations()
{
    const char * string = "  testing  ";
    char * result; 
    if (!is_memory_initialized()){ 
        initmemory(); 
    }
    result = strduplicate(string); 
    printf("|%s|%s|\n", string, result);
    myfree(result); 
    memorymap(); 
    result = strltrim(string); 
    printf("|%s|%s|\n", string, result);
    myfree(result); 
    memorymap(); 
    result = strrtrim(string); 
    printf("|%s|%s|\n", string, result);
    myfree(result); 
    memorymap(); 
    result = strlrtrim(string); 
    printf("|%s|%s|\n", string, result);
    myfree(result); 
    memorymap(); 
}
