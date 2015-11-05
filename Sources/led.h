#ifndef _LED_H
#define _LED_H value
#define NUM_OF_LEDS 4

#define LED_ORANGE_PORTA_BIT 11
#define LED_YELLOW_PORTA_BIT 28
#define LED_GREEN_PORTA_BIT 29
#define LED_BLUE_PORTA_BIT 10

#ifndef PORT_PCR_MUX_ANALOG
#define PORT_PCR_MUX_ANALOG 0
#endif
#ifndef PORT_PCR_MUX_GPIO
#define PORT_PCR_MUX_GPIO 1
#endif

typedef struct _led_t {
    void (*init)(void); 
    void (*write)(int ch); 
} led_t;

void ledOrangeConfig(void);
void ledYellowConfig(void);
void ledGreenConfig(void);
void ledBlueConfig(void);

void ledOrangeOff(void);
void ledYellowOff(void);
void ledGreenOff(void);
void ledBlueOff(void);

void ledOrangeOn(void);
void ledYellowOn(void);
void ledGreenOn(void);
void ledBlueOn(void);

void ledInitAll(void);

int ledinit(void *minorno); 
int ledwrite(int ch, void *minorno);
#endif

