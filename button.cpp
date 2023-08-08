#include "gpio.h"
#include <Arduino.h>
#include "button.h"

#define LOGGER_ENABLED 1
#define LOGGER_LEVEL LOG_INFO
#include "logger.h"

/* ugly source include since Arduino does not support source/config directories */
#include "hw_config/button_cfg.cpp"


static inline bool isDebounced(Button_Struct *button){
    uint32_t timePoint = button->pressedTimePoint;
    return (millis() - timePoint) > debounceDelay;
}


static void buttonReleasedStateMachine(Button_Struct *button){
    Button_State state = button->logicState;

    switch(state){
        case BUTTON_STATE_SHORT_PRESS:

            state = BUTTON_STATE_SHORT_RELEASED;
            break;

        case BUTTON_STATE_LONG_PRESS:
            state = BUTTON_STATE_LONG_RELEASED;
            break;

        case BUTTON_STATE_SUPERLONG_PRESS:
            state = BUTTON_STATE_SUPERLONG_RELEASED;
            break;

        case BUTTON_STATE_SHORT_RELEASED:
        case BUTTON_STATE_LONG_RELEASED:
        case BUTTON_STATE_SUPERLONG_RELEASED:
        case BUTTON_STATE_SENTINEL:
        default:
            /* this is the last state */
            /* do nothing */
            break;
    }

    if(state != button->logicState){
        button->logicState = state;
        LOGGER(LOG_DEBUG, "Button released no:");
        LOGGER(LOG_DEBUG, button->pinName, DEC);
        LOGGER(LOG_DEBUG, " state:");
        LOGGERLN(LOG_DEBUG, state, DEC);
    }
}


static void buttonPressedStateMachine(Button_Struct *button){
    Button_State state = button->logicState;
    uint32_t pressedTime = millis() - button->pressedTimePoint;

    switch(state){
        case BUTTON_STATE_SHORT_PRESS:
            if(pressedTime > longPressTime){
                state = BUTTON_STATE_LONG_PRESS;
            }
            break;

        case BUTTON_STATE_LONG_PRESS:
            if(pressedTime > superLongPressTime){
                state = BUTTON_STATE_SUPERLONG_PRESS;
            }
            break;

        case BUTTON_STATE_SUPERLONG_PRESS:
            /* this is the last state */
            /* do nothing */
            break;

        case BUTTON_STATE_SHORT_RELEASED:
        case BUTTON_STATE_LONG_RELEASED:
        case BUTTON_STATE_SUPERLONG_RELEASED:
        case BUTTON_STATE_SENTINEL:
        default:
            state = BUTTON_STATE_SHORT_PRESS;
            break;
    }

    if(state != button->logicState){
        button->logicState = state;
        LOGGER(LOG_INFO, "Button pressed no:");
        LOGGER(LOG_INFO, button->pinName, DEC);
        LOGGER(LOG_INFO, " state:");
        LOGGERLN(LOG_INFO, state, DEC);
    }
}


Button_Struct * Button_FindHandler(Gpio_Pin pinName){
    for(uint8_t i=0; i < (sizeof(buttonStateMatrix)/sizeof(buttonStateMatrix[0])); i++){
        Button_Struct * button = &buttonStateMatrix[i];
        if(button->pinName == pinName){
            return button;
        }
    }

    /*if didn't find: */
    return NULL;
}


void buttonTask(void){
    for(uint8_t i=0; i < (sizeof(buttonStateMatrix)/sizeof(buttonStateMatrix[0])); i++){
        Button_Struct * button = &buttonStateMatrix[i];

        bool newPhysState = Gpio_GetPinState(button->pinName);
        if(newPhysState != button->physState){
            button->pressedTimePoint = millis();
            button->physState = newPhysState;
        }

        if(isDebounced(button)){
            if (button->physState == HIGH) {
                buttonPressedStateMachine(button);
            }else{
                buttonReleasedStateMachine(button);
            }
        }

    }
}

