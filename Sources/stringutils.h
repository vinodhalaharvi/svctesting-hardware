//Author: Vinod Halaharvi
#ifndef __STRINGUTILS_H
#define __STRINGUTILS_H value
char * strcopy(char * dst, const char * src); 
unsigned strlength(const char * string); 
char * stralloc(unsigned len); 
char * strduplicate(const char * src); 
char * strltrim(const char * src); 
char * strrtrim(const char * src); 
char * strlrtrim(const char * src); 
void memoryset(void *memory, char ch, unsigned len); 
unsigned strcompare(const char * s1, const char * s2); 
void verify_string_operations(); 
#endif
