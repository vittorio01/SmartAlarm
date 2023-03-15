#ifndef __HARDWARE_H__
#define __HARDWARE_H__
#include <stdbool.h>
#include "libraries/Crystalfontz128x128_ST7735.h"
#include "libraries/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"

/* PINS DEFINE */
// BUTTONS
#define BUT_S1_PORT_INT INT_PORT5
#define BUT_S1_PORT GPIO_PORT_P5
#define BUT_S1_PIN GPIO_PIN1

#define BUT_S2_PORT_INT INT_PORT3
#define BUT_S2_PORT GPIO_PORT_P3
#define BUT_S2_PIN GPIO_PIN5

// LEDS
#define RGB_LED_BLUE_PORT GPIO_PORT_P5
#define RGB_LED_BLUE_PIN GPIO_PIN6
#define RGB_LED_RED_PORT GPIO_PORT_P2
#define RGB_LED_RED_PIN GPIO_PIN6
#define RGB_LED_GREEN_PORT GPIO_PORT_P2
#define RGB_LED_GREEN_PIN GPIO_PIN4

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
#define JOY_B_PORT_INT INT_PORT4

#define BUZZER_PORT GPIO_PORT_P2
#define BUZZER_PIN GPIO_PIN7

/* TIMERS STRUCTS */
typedef enum {TIMER1,TIMER2,TIMER3,NONE} timerNumber;
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

/* JOYSTICK STRUCTS */
typedef struct joystick {
    int_fast8_t joyXvalue;
    int_fast8_t joyYvalue;
}joystick;

/* BUTTONS STRUCTS */
volatile typedef struct ButtonStatus{
    volatile uint8_t b1;     // if it's !=0 the button1 was pressed, else not (must be resetted by user, setted by button's IRQ)
    volatile uint8_t b2;
    volatile uint8_t jb;   // same as button1 but for joystick button
}ButtonStatus;

/* GENERALS INIT. */
void initHardware(Graphics_Context* gc);

/* MODULES INIT. */
void initPCM();
void initClockSystem();
void initTimerSystem();
void initButtonSystem();    // set all the buttons configurations
void initLedSystem();       // set all the leds port
void intiDisplaySystem(Graphics_Context* gc);
void initAdcSystem();       //set all the adc input pin (single mode)
void initRTCSystem();

/* TIMER FUNCTIONS */
//the function generate_delay verifies if there is an available timer and configures it with a delay and a specific handler:
// - The delay can be a value from 1ms to 32760ms
// - The handler is called only once time and the timer automatically reset its functions
// - The function returns back a value timerNumber which identifies the assigned timer (assume NONE if all timers are busy or there is an argument error)
// - The timer can be stopped with the function disable_timer
timerNumber generate_delay(const uint16_t delay, void* handler);

//the function generate_rate verifies if there is an available timer and configures it with a delay and a specific handler:
// - The delay can be a value from 1ms to 32760ms
// - The handler is automatically called infinite times with the specified delay
// - The function returns back a value timerNumber which identifies the assigned timer (assume NONE if all timers are busy or there is an argument error)
// - The timer can be stopped with the function disable_timer
timerNumber generate_rate(const uint16_t delay, void* handler);

//This function generates a tone with boosterpack buzzer.
//Frequency value must be between 3Hz and 250Khz and the volume must be a value between 1 and 100 (otherwise the function will not start)
void generate_tone(const uint16_t frequency, const uint16_t volume);

//This function turn off the buzzer tone
void disable_tone();

//the function disable_timer stops the specified timer.
void disable_timer(timerNumber timer);

Timers timerlist;

/* BUTTONS FUNCTIONS */
ButtonStatus buttonsPressed;        // example: if buttonsPressed.b1 == 1 means it was pressed (to be reseted after use)
void resetButtonsState();           // reset all the button states

/* ADC FUNCTIONS */
volatile joystick JoyValues;
void startADCconversions();
void stopADCconversions();
joystick getJoyValue(); // return the joystick X & Y values (0-255)

/* RTC FUNCTIONS */


#endif
