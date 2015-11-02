/* Source copied from CSCIE-92 class sample code */
#ifndef _UART_H
#define _UART_H
#define NUM_OF_UARTS 1

typedef struct _uart_t {
    void (*init)(void); 
    int (*write)(int ch); 
    int (*read)(); 
} uart_t;


int uart_init(void *minorno); 
int uart_write(int ch, void *minorno);
int uart_read(void *minorno);
//int uart_writestring(char *string, void *minorno);
#endif
