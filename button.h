
#if !defined BUTTON_H_GUARD
#define BUTTON_H_GUARD


#include "gpio.h"


typedef enum {
    BUTTON_STATE_SHORT_RELEASED,
    BUTTON_STATE_SHORT_PRESS,
    BUTTON_STATE_LONG_PRESS,
    BUTTON_STATE_LONG_RELEASED,
    BUTTON_STATE_SUPERLONG_PRESS,
    BUTTON_STATE_SUPERLONG_RELEASED,
    BUTTON_STATE_SENTINEL,
} Button_State;


typedef void (*Button_Callback)(void);


typedef struct{
    const Gpio_Pin pinName;
    Button_State logicState;
    bool physState;
    uint32_t pressedTimePoint;
    Button_Callback *buttonCallback[BUTTON_STATE_SENTINEL];
} Button_Struct;


void buttonTask(void);



#endif

