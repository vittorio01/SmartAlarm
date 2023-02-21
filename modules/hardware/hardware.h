#ifndef __HARDWARE_H__
#define __HARDWARE_H__
#include <stdbool.h>
#include "libraries/Crystalfontz128x128_ST7735.h"
#include "libraries/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include "main.h"


/* PINS DEFINE */
// BUTTONS
#define BUT_S1_PORT_INT INT_PORT5
#define BUT_S1_PORT GPIO_PORT_P5
#define BUT_S1_PIN GPIO_PIN1

// LEDS
#define RGB_LED_BLUE_PORT GPIO_PORT_P5
#define RGB_LED_BLUE_PIN GPIO_PIN6

// JOYSTICK
#define JOY_X_PORT GPIO_PORT_P6
#define JOY_X_PIN GPIO_PIN0
#define JOY_X_INT ADC_INT15
#define JOY_X_MEM ADC_MEM15
#define JOY_X_ADC_CH ADC_INPUT_A15
#define JOY_Y_PORT GPIO_PORT_P4
#define JOY_Y_PIN GPIO_PIN4
#define JOY_Y_INT ADC_INT9
#define JOY_Y_MEM ADC_MEM9
#define JOY_Y_ADC_CH ADC_INPUT_A9
#define JOY_B_PORT GPIO_PORT_P4
#define JOY_B_PIN GPIO_PIN1

/* TIMERS STRUCTS */
typedef enum {TIMER0,TIMER1,TIMER2,TIMER3,UNDEFINED} timerNumber;
typedef enum {DELAY,RATE,PWM,NOT_USED} timerType;

typedef struct Timers {
    void (*timer0_handler)(void);
    void (*timer1_handler)(void);
    void (*timer2_handler)(void);
    void (*timer3_handler)(void);
    timerType timer0_type;
    timerType timer1_type;
    timerType timer2_type;
    timerType timer3_type;
} Timers;

/* ADC STRUCTS */


/* GENERALS INIT. */
void initHardware(Graphics_Context* gc);

/* MODULES INIT. */
void initClockSystem();
void initTimerSystem();
void initButtonSystem();    // set all the buttons configurations
void initLedSystem();       // set all the leds port
void intiDisplaySystem(Graphics_Context* gc);
void initAdcSystem();       //set all the adc input pin (single mode)

/* TIMER FUNCTIONS */
timerNumber generate_delay(const uint16_t delay, void* handler);

timerNumber generate_rate(const uint16_t delay, void* handler);

timerNumber generate_pwm(const uint16_t frequency, const uint16_t volume,const uint8_t port, const uint8_t pin);

bool disable_timer(timerNumber timer);

Timers timerlist;

/* BUTTONS FUNCTIONS */


/* ADC FUNCTIONS */
void enableJoyInterrupt();  //enable the joystick adc interrupt
void disableJoyInterrupt(); //disable the joystick adc interrupt



#endif
