/* Source copied from CSCIE-92 class sample code */
#ifndef _LCDC_H
#define _LCDC_H
#define NUM_OF_LCDCS 1 

typedef struct _lcdcd_t {
    void (*init)(void); 
    int (*write)(int ch); 
} lcdc_t;

void lcdcInitAll(void);
int lcdc_init(void *minorno); 
int lcdc_write(int ch, void *minorno);
#endif

