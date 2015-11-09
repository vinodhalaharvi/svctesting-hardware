#ifndef _COMMON_H
#define _COMMON_H 
extern unsigned mystdin; 
extern unsigned mystdout; 
typedef enum { false, true } boolean; 
void myassert(unsigned status, const char * expected, const char * actual); 
void write_string(const char *p, unsigned mystdout); 
#endif
