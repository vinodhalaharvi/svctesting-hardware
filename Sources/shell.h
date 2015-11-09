#ifndef _SHELL_H
#define _SHELL_H value
#include "common.h"
//header file for shell.c
const int LINE_MAX = 256;
typedef int (*command_func_type) (int argc, char * argv[]); 
typedef struct _myclock_t {
    struct { 
        unsigned hour; 
        unsigned minute; 
        unsigned second; 
    } data; 
} myclock_t;

int cmd_date(int argc, char *argv[]);
int cmd_echo(int argc, char *argv[]);
int cmd_exit(int argc, char *argv[]);
int cmd_help(int argc, char *argv[]);
int cmd_set(int argc, char *argv[]); 
int cmd_malloc(int argc, char *argv[]);
int cmd_free(int argc, char *argv[]);
int cmd_memorymap(int argc, char *argv[]);
int cmd_verifymemalloc(int argc, char *argv[]); 

int process_line(char line[LINE_MAX + 1], int *argc, char * argv[]);
void stringsplit(char line[LINE_MAX +1], char * delimiter, int *argc, char *argv[]);
command_func_type get_command_function(char line[LINE_MAX+1], int *argc, char * argv[]); 
int do_command(char line[LINE_MAX + 1], int *argc, char * argv[]); 
void print_error(char line[LINE_MAX +1], int *argc, char * argv[]); 
char *join(char * stringArray[], char * delimiter); 
boolean isSlash(char ch); 
char subescapse_char(char ch); 
void double_quote_check(int *ch);
void splitString(char * string, char delimiter, char **store[], int *howmany); 
void printStringArray(char *stringArray[], int howmany); 
int getNumDaysInThisMonth(long year, long month); 
void calendar(unsigned long days, unsigned long seconds, unsigned long useconds); 
boolean is_leap_year(int year); 
char * toString(int monthno);
void init(myclock_t *clock); 
void timeofday(myclock_t * clock, unsigned long seconds); 
void shellfree(char *array[], unsigned howmany); 
int print_string(int argc, char *argv[]);
int cmd_fopen(int argc, char *argv[]); 
int cmd_fclose(int argc, char *argv[]); 
int cmd_fgetc(int argc, char *argv[]); 
int cmd_fputc(int argc, char *argv[]); 
int cmd_delete_file(int argc, char *argv[]);
int cmd_create_file(int argc, char *argv[]); 
int cmd_ls(int argc, char *argv[]); 
int cmd_cat(int argc, char *argv[]); 
#endif
