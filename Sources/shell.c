#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "map.h"
#include "shell.h"
#include "limits.h"
#include "mymalloc.h"
#include "common.h"
#include "stringutils.h"
#include "mymalloctesting.h"
#include "io.h"
#include "assert.h"
#include "mcg.h"
#include "sdram.h"
#include "uart.h"
#include "lcdc.h"
#include "lcdcConsole.h"
#include "svc.h"
#include "stdio.h"

#include "uartdriver.h"
#define CHAR_EOF 4

#include "mcg.h"
#include "sdram.h"

#define MAX_STRING_LENGTH 1000
#define MAX_STRING_LARGE_SIZE 1000
#define MAX_COMMAND_LINE_ARGUMENTS 100
typedef unsigned long uintptr_t; 
//Vinod Halaharvi
//HUID: 80778287
//vinod.halaharvi@gmail.com, (904) 200 1070
boolean isline(char line[LINE_MAX +1]) ; 
static int inside_double_quote = 0; 

//Enumerator for error codes for this shell
typedef enum {
    SUCCESS, 
    COMMAND_NOT_FOUND
} error;

// Months string literals
const char * months[12]= { 
    "January", 
    "Febrauary", 
    "March", 
    "April", 
    "May", 
    "June", 
    "July", 
    "August", 
    "September", 
    "October", 
    "November", 
    "December"
}; 

// string to function object map
struct commandEntry {
    const char *name;
    int (*functionp)(int , char *[]);
} commands[] = {
    {"echo", cmd_echo},
    {"date", cmd_date},
    {"exit", cmd_exit},
    {"help", cmd_help}, 
    {"set", cmd_set}, 
    {"malloc", cmd_malloc}, 
    {"free", cmd_free}, 
    {"fopen", cmd_fopen}, 
    {"fclose", cmd_fclose}, 
    {"myread", cmd_fgetc}, 
    {"fputc", cmd_fputc}, 
    {"memorymap", cmd_memorymap}, 
    {"rm", cmd_delete_file}, 
    {"touch", cmd_fopen}, 
    {"ls", cmd_ls}, 
    {"cat", cmd_cat}, 
    {NULL, NULL}
};

//each node will store a name value pair mapping
//of the environment variable
static node_type * env = NULL; 

void initialize_hardware(){ 
    mcgInit();
    sdramInit();
    SVCUartInit(0); 
    SVCLcdcInit(0);
    initmemory(); 
    mystdin = SVCMyopen("/dev/uart/1", 0); 
    mystdout = SVCMyopen("/dev/lcdc/1", 0); 
}

/*
    while(1) {
        char ch = uartGetchar(UART2_BASE_PTR); 
        //char ch = uart_read(0);
        SVCUartWrite(ch, 0);
        SVCLcdcWrite(ch, 0); 
    }
*/


//prompt a '$' and wait for user input
//until a newline and then process the line 
//and optionally print code if error happened
int main() {
    int argc; 
    char **argv = NULL; 
    char line[LINE_MAX + 1];
    int c, index;
    index = 0;
    initialize_hardware(); 
    //setvbuf(mystdin, NULL, _IONBF, 0);
    write_string("Memory allocated ..", mystdout);
    //verify_string_operations(); 
    //verify_device_independent_file_operations(); 
    write_string("Ready to accept user commands", mystdout);
    while(1){ 
        write_string("$ ", mystdout); 
        //fflush(mystdout); 
        c = myread(mystdin);
        while (c > 0 && c != '\n' && index < LINE_MAX) {
            if (isSlash(c)) { 
                c = myread(mystdin); 
                c = subescapse_char(c); 
            }
            double_quote_check(&c); 
            line[index++] = c;
            c = myread(mystdin);
        }
        myassert(!inside_double_quote, "", "!inside_double_quote"); 
        line[index] = '\0';

        process_line(line, &argc, argv);
        index = 0; 
        /*if (ferror(mystdin)) {
            sprintf(print_string, "Error while reading line: %s\n", 
                    strerror(errno));
            exit(EXIT_FAILURE); 
            return 1;
        } else {
            process_line(line, &argc, argv);
            index = 0; 
        }*/
    }
    myfree(argv); 
    exit(EXIT_SUCCESS); 
}


//currently nothing is being freed. 
//free feature is missing. Use of strdup is causing 
//issues during free. Will have to get rid of it
//to make free working
void shellfree(char *array[], unsigned howmany){ 
    myassert(array != NULL, "", "array != NULL"); 
    myassert((int) howmany > 0, "", "(int) howmany > 0"); 
    unsigned i = 0; 
    for (i = 0; i < howmany; ++i) {
        myfree(array[i]); 
    }
    return; 
}


//not an ideal implementation, but gets the job done
char *join(char * stringArray[], const char * delimiter){ 
    char * result = (char *) mymalloc(MAX_STRING_LARGE_SIZE); 
    char * base = result; 
    int i;
    memoryset(result, '\0', MAX_STRING_LARGE_SIZE); 
    i = 0; 
    while(stringArray != NULL && stringArray[i]){ 
        strcopy(result, stringArray[i]); 
        result += strlength(stringArray[i]); 
        if (stringArray[i+1] != NULL) { 
            strcopy(result, delimiter); 
            result += strlength(delimiter); 
        }
        i++; 
    }
    return base;
}

int cmd_date(int argc, char *argv[]){ 
    myassert(argc == 1, "", "argc == 1"); 
    myassert(argv != NULL, "", "argv == NULL"); 
    return 0;
}

//wrote this date function from scratch
//first get the number of days since epoch 
//and then pass days to the calendar function 
//to print the current date. 
/*int cmd_date(int argc, char *argv[]){ 
  int result;
  struct timeval time_value; 
  unsigned long  seconds, minutes, hours; 
  unsigned long  useconds; 
  unsigned long days; 
  myassert(argc == 1, "", "argc == 1"); 
  memoryset(&time_value, '\0', sizeof(struct timeval)); 
  result = gettimeofday(&time_value, NULL); 
  myassert(result == 0, "", "return == 0"); 
  seconds = time_value.tv_sec; 
  useconds = time_value.tv_usec; 
  minutes = seconds/60; 
  hours =  minutes/60; 
  days =  hours/24;
//calendar function to convert from epoch days 
//to current datetime in the current locale
calendar(days, seconds, useconds); 
return 0; 
}*/

int cmd_malloc(int argc, char *argv[]){
    void * addr;
    unsigned val; 
    char print_string[1000]; 
    myassert(argc == 2, "", "argc == 2"); 
    val = strtoul(argv[1], NULL, 10);
    addr = (void *) mymalloc(val); 
    if (addr) { 
        sprintf(print_string, "%p\n", addr);
        write_string(print_string, mystdout); 
        return 0; 
    } else { 
        sprintf(print_string, "%s\n", "Memory allocation failed ..");
        write_string(print_string, mystdout); 
        return 127; 
    }
    //myfree(addr); 
}


int cmd_free(int argc, char *argv[]){
    unsigned long val; 
    myassert(argc == 2, "", "argc == 2"); 
    val = strtoul(argv[1], NULL, 16);
    myfree((void *) (uintptr_t) val); 
    return 0; 
}

int cmd_memorymap(int argc, char *argv[]){
    myassert(argc == 1, "", "argc == 1"); 
    myassert(argv != NULL, "", "argv == NULL"); 
    memorymap(); 
    return 0; 
}


//echo command implementation
int cmd_echo(int argc, char *argv[]){ 
    char print_string[1000]; 
    myassert(argc > 0, "", "argc > 0"); 
    argv[argc] = NULL; 
    sprintf(print_string, "%s\n", join(++argv, " ")); 
    write_string(print_string, mystdout); 
    return 0;
}

//environment variables are not fully implemented
//like variable replacements are not implemented, 
//but set is working and set without any arguments
//is working as well
int cmd_set(int argc, char *argv[]){ 
    char *values[2]; 
    int count = 0; 
    if (match(argv[0], "set")){ 
        if (argc == 1){ 
            print(env); 
        } else { 
            stringsplit(argv[1], "=", &count, values); 
            myassert(count == 2, "", "count == 2"); 
            env = put(env, values[0], values[1]); 
        }
    }
    return 0;
}

//helper function to convert to long
//with error checking
long toLong(char * string, int base){ 
    /* Code from strtol man page documentation */
    char * endptr; 
    errno = 0; 
    long val; 
    val = strtol(string, &endptr, base);
    myassert (!(errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0), "", "Failed on errno"); 
    myassert (endptr != string, "", "endptr != string"); 
    return 0; 
}


//helper function to convert to unsigned long
//with error checking
long toUnsignedLong(char * string, int base){ 
    /* Code from strtol man page documentation */
    errno = 0; 
    char * endptr; 
    long val; 
    val = strtoul(string, &endptr, base);
    myassert ((!(errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
                || (errno != 0 && val == 0)), "", 
            "(!(errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0))"); 
    myassert (endptr != string, "", "endptr != string"); 
    return 0;
} 


//call exit system call with passed in 
//error code
int cmd_exit(int argc, char *argv[]){ 
    long exit_code; 
    if (argc > 1) { 
        exit_code = toLong(argv[1], 10); 
        exit(exit_code); 
    } else { 
        exit(0); 
    }
    return 0;
}


//show very simple help of all commands
int cmd_help(int argc, char *argv[]){ 
    myassert(argc == 1, "", "argc == 1"); 
    char print_string[1000]; 
    sprintf(print_string, "%s\n", "The following commands are available");
    write_string(print_string, mystdout); 
    int i = 0; 
    while(commands[i].name){ 
        sprintf(print_string, "%s\n", commands[i].name);
        write_string(print_string, mystdout); 
        i++; 
    }
    return 0;
}

//process each line
int  process_line(char line[LINE_MAX + 1], int *argc, char * argv[]) {
    char print_string[1000]; 
    int result; 

    //is the line empty
    if (!isline(line)){ 
        return 0;  
    }

    line = strlrtrim(line); 

    //split the line and generate argv
    //and also populate the number of arguments as well
    //note here argc is a integer pointer 
    //and will be filled by splitString function
    splitString(line, ' ', &argv, argc); 
    myassert(argc != 0, "", "argc"); 

    //now we are ready to run the command
    //and get the result. 0 result is successful exec 
    //and non 0 is a failed exec
    result = do_command(line, argc, argv); 
    if (result != 0){ 
        sprintf(print_string, "Non zero return value of %d while running command, %s\n", 
                result, line);
        write_string(print_string, mystdout); 
    }
    int i;
    for (i = 0; i < *argc; ++i) {
        myfree(argv[i]);
    }
    return result;
}


//helper function to check if line is empty 
boolean isline(char line[LINE_MAX +1]){ 
    int i = 0; 
    myassert(line != NULL, "", "line != NULL"); 
    while(line[i] != '\0' && line[i] != '\n'){ 
        if (line[i] != ' '){ 
            return true; 
        }
        i++; 
    }
    return false; 
}


//helper function to split
//don't like the strtok, and will be removed 
//in the future psets
void stringsplit(char line[LINE_MAX +1], const char * delimiter, 
        int *argc, char *argv[]){
    char *string; 
    string = strtok(line, delimiter); 
    int count = 0; 
    while(string){ 
        //sprintf(print_string, "%s\n", string);
        argv[count++] = strduplicate(string); 
        //free(string);  ? shouldn't this be freed
        string = strtok(NULL, delimiter); 
    }
    *argc = count; 
    return; 
}

//look function object using function name 
//and return the function pointer
command_func_type get_command_function(char line[LINE_MAX+1], 
        int *argc, char * argv[]){ 
    int i =0; 
    while(commands[i].name != NULL){ 
        if (strcompare(commands[i].name, argv[0]) == 0 ){ 
            return commands[i].functionp; 
        } 
        i++;
    }
    return NULL; 
}


//look up the command and get Command function pointer
//and exec the command. get the result and return the 
//result
int do_command(char line[LINE_MAX + 1], int *argc, char * argv[]){ 
    char print_string[1000]; 
    int (*func)(int argc, char * argv[]); 
    int result; 
    myassert(argv != NULL, "", "argv != NULL"); 
    myassert(argc > 0, "", "argc > 0"); 
    func = get_command_function(line, argc, argv); 
    //assert(func); 
    if (func == NULL){ 
        sprintf(print_string, "Command %s not found \n", argv[0]); 
        write_string(print_string, mystdout); 
        result = COMMAND_NOT_FOUND; 
    } else { 
        result = func(*argc, argv); 
    }
    return result; 
}

//helper to print boolean
void print_boolean(boolean bool){ 
    char print_string[1000]; 
    switch (bool) {
        case false:
            sprintf(print_string, "%s\n", "false");
            write_string(print_string, mystdout); 
            break;
        case true:
            sprintf(print_string, "%s\n", "true");
            write_string(print_string, mystdout); 
        default:
            myassert(0, "", "0"); 
    }
    return;
}


/*functions.  Keep in mind that some years are leap years and others
  are not.  Leap years contain 366 days (February 29th) and all other
  years contain 365 days.  Every year that is evenly divisible by
  four is a leap year, except that every year divisible by 100 is not
  a leap year, except that every year divisible by 400 is a leap
  year.
  assert(is_leap_year(1900) == false); 
  assert(is_leap_year(2011) == false); 
  assert(is_leap_year(2000) == true); 
  */
boolean is_leap_year(int yearno){ 
    if (yearno % 4 == 0 ){ 
        if (yearno % 100 == 0){ 
            if (yearno % 400 == 0) { 
                return true; 
            }
            return false; 
        } 
        return true; 
    } else { 
        return false; 
    }
}

//simple helper function
boolean isSlash(char ch){ 
    return ch == '\\'; 
}


//escape character support
char subescapse_char(char ch){ 
    switch (ch) {
        case '0': return '\0'; 
        case 'a': return '\a'; 
        case 'b': return '\b'; 
        case 'e': return '\e';
        case 'f': return '\f';
        case 'n': return '\n';
        case 'r': return '\r';
        case 't': return '\t'; 
        case 'v': return '\v';
        default: return ch;
    }
}

/*
   Extra credit: Allow fields on the line to be double-quote delimited
   strings that can contain spaces or tabs.  Ensure that any such
   field has a matching open double-quote and close double-quote.
   Also, allow a double-quote to appear within a double-quoted field
   in either or both of two possible ways: (1) allow two adjacent
   double-quotes within a double-quoted field to denote a single
   double-quote within the field, (2) implement the following
   backslash escape notation to allow special characters within a
   double-quoted string. 
   */
//double quotes is not completely working
//specially the edge cases, but is working 
//for most part
void double_quote_check(int *ch){ 
    if (*ch == 34){ 
        //clobber consecutive double quotes
        while ((*ch = myread(mystdin)) == 34);  

        //toggle every time we see a non consecutive double quote
        inside_double_quote = !inside_double_quote; 
    }
    return; 
}

//clobber consecutive spaces 
char *  clobberspaces(char * src, char delimiter){ 
    int i =0, j =0;  
    myassert(src != NULL, "", "src != NULL"); 
    char * dst = (char *) mymalloc(strlength(src) + 1); 
    //memoryset(dst, '\0', strlength(src)); 
    while(src[i]){ 
        if (!(src[i] == delimiter && src[i+1] == delimiter ))
            dst[j++] = src[i];  
        i++; 
    }
    dst[j] = '\0'; 
    return dst;
}

//split string and populate store (argc) and argc
//howmany = argc
void splitString(char * string, char delimiter, 
        char **store[], 
        int *howmany){ 
    int i = 0; 
    int argc = 0;
    char * clbrstring; 
    char * head; 
    myassert (string != NULL, "", "string != NULL"); 
    //remove consecutive spaces
    clbrstring = clobberspaces(string, ' ');

    head = clbrstring; 
    *howmany = 0; 
    unsigned argcount = 0; 

    // count the number of arguments first
    while(clbrstring[i]){ 
        if (clbrstring[i] ==  delimiter 
                && clbrstring[i+1] != delimiter) { 
            argcount++; 
        } 
        i++; 
    }

    //allocate space for argcount number of arguments
    *store = (char **) mymalloc((argcount+1) * sizeof(char *)); 
    (*store)[argcount] = NULL; 

    //create argv now
    i = 0;
    while(clbrstring[i]){ 
        if (clbrstring[i] ==  delimiter && clbrstring[i+1] != delimiter) { 
            //this is some arbitrary limit
            myassert(argc < MAX_COMMAND_LINE_ARGUMENTS, "", 
                    "argc < MAX_COMMAND_LINE_ARGUMENTS"); 
            clbrstring[i++] = '\0'; 
            (*store)[argc++] = strduplicate(head);  
            (*howmany)++; 
            head = clbrstring + i; 
        }
        i++; 
    }

    //edge case
    if (!argc){ 
        (*store)[0] = strduplicate(string); 
        *howmany = 1; 
        (*store)[1] = NULL; 
    } else { 
        (*store)[argc++] = head; 
        (*howmany)++; 
        (*store)[argc] = NULL; 
    }
    myfree(clbrstring); 
    myfree(string); 
}


//helper function to print array of strings to console
void printStringArray(char *stringArray[], int howmany){ 
    char print_string[1000];
    myassert(stringArray != NULL, "",
            "stringArray != NULL"); 
    int i =0; 
    for (i = 0; i < howmany; ++i) {
        sprintf(print_string, "%s\n", stringArray[i]); 
        write_string(print_string, mystdout); 
    }
    return; 
}


//get how many days in a month
//# of days in a month depends on if the year is a leap year
int getNumDaysInThisMonth(long year, long month){ 
    //static map of leap month days (lmdays)  and  
    //nonleap month days (nlmdays)
    static int lmdays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ; 
    static int nlmdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
    if (is_leap_year(year)){ 
        return lmdays[month]; 
    } else { 
        return nlmdays[month]; 
    }
}


//convert epoch days to calendar date in the current locale.
//the residue of the seconds left after the day conversion 
//should be the time of today
void calendar(unsigned long days, 
        unsigned long seconds, unsigned long useconds){ 
    unsigned long year = 1970, month = 0; 
    unsigned long daycount = 0; 
    unsigned long dayofmonth = 1; 
    myclock_t clock; 
    while (1) { 
        daycount += 1; 
        dayofmonth += 1; 
        if (daycount == days) { 
            break; 
        }
        if (dayofmonth >  getNumDaysInThisMonth(year, month)) { 
            month++; 
            dayofmonth = 1; 
            if (month >= 12 ) { 
                year++; 
                month = 0; 
            }
        } 
    }
    //total seconds minus the seconds of the days so far 
    //will give us time since this day started 
    //which is also the current time of the day
    timeofday(&clock, seconds - 60 * 60 * 24 * daycount); 

    //"January 23, 2014 15:57:07.123456"
    char print_string[1000]; 
    sprintf(print_string, "%s %.2lu, %.4lu %.2u:%.2u:%.2u.%.6lu\n", 
            toString(month), dayofmonth, year, 
            clock.data.hour, 
            clock.data.minute, 
            clock.data.second, 
            useconds
          );
    write_string(print_string, mystdout); 
}


//simple helper function
char * toString(int monthno){ 
    static char * stringMonths[12]= { 
        "January", 
        "Febrauary", 
        "March", 
        "April", 
        "May", 
        "June", 
        "July", 
        "August", 
        "September", 
        "October", 
        "November", 
        "December"
    }; 
    myassert(monthno < 12, "", "monthno < 12"); 
    return stringMonths[monthno]; 
}

//initialize the close
void init(myclock_t *clock){ 
    clock->data.hour = 0; 
    clock->data.minute = 0; 
    clock->data.second =0; 
}

//take the number of residual seconds since this day started
//and convert to the time of this day
void timeofday(myclock_t * clock, unsigned long seconds){ 
    unsigned minutes = 0, hours = 0; 
    myassert(seconds <= 60 * 60 *  24, "", 
            "seconds <= 60 * 60 *  24"); 
    minutes = seconds / 60; 
    hours = minutes / 60; 
    clock->data.hour = hours; 
    clock->data.minute = (seconds - (clock->data.hour * 60 * 60)) / 60; 
    clock->data.second = (seconds - (clock->data.hour * 60 * 60) - 
            clock->data.minute * 60); 
}

int cmd_fopen(int argc, char *argv[]){
    unsigned fd; 
    char print_string[1000]; 
    init_fdtable(); 
    myassert(argc == 2, "", "argc == 2"); 
    sprintf(print_string, "%s %s\n", argv[0], argv[1]);
    write_string(print_string, mystdout); 
    fd = myopen(argv[1], FILE_CREATE); 
    sprintf(print_string, "fd = %d\n", fd);
    write_string(print_string, mystdout); 
    return fd; 
}

int cmd_fclose(int argc, char *argv[]){
    unsigned fd; 
    myassert(argc == 2, "", "argc == 2"); 
    fd = strtoul(argv[1], NULL, 10);
    myclose(fd); 
    return 0;
}

int cmd_fgetc(int argc, char *argv[]){
    unsigned fd; 
    int ch; 
    char print_string[1000]; 
    myassert(argc == 2, "", "argc == 2"); 
    fd = strtoul(argv[1], NULL, 10);
    ch = myread(fd); 
    sprintf(print_string, "%c\n", ch);
    write_string(print_string, mystdout); 
    return 0;
}

int cmd_delete_file(int argc, char *argv[]){
    myassert(argc == 2, "", "argc == 2"); 
    delete_file(argv[1]); 
    return 0;
} 

int cmd_ls(int argc, char *argv[]){
    myassert(argc == 1, "", "argc == 1"); 
    ls(); 
    return 0; 
}

int cmd_cat(int argc, char *argv[]){
    unsigned ch; 
    char print_string[1000]; 
    myassert(argc == 2, "", "argc == 2"); 
    char * filename =  argv[1]; 
    unsigned fd = myopen(filename, FILE_CREATE); 
    myassert(fd >= 0, "" , "fd >=0"); 
    while((ch = myread(fd)) != EOF){ 
        fputc(ch, mystdout); 
    }
    sprintf(print_string, "\n");
    write_string(print_string, mystdout); 
    //fflush(mystdout); 
    return 0;
}

int cmd_fputc(int argc, char *argv[]){
    unsigned fd; 
    myassert(argc == 3, "", "argc == 3"); 
    fd = strtoul(argv[1], NULL, 10);
    int ch =  argv[2][0]; 
    mywrite(fd, ch); 
    return 0;
}
