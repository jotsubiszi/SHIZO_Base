#include "gpio.h"
#include <Arduino.h>
#include "button.h"


static void dummy(void){
    static uint8_t i;
        Serial.print("DUMMY:");
        Serial.println(i++, DEC);
}



Button_Struct buttonStateMatrix[/*do not set array size explicitly (checked by assert)*/] = {
    {GPIO_PIN_BUTTON1, BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON2, BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON3, BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON4, BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON5, BUTTON_STATE_SHORT_RELEASED, false, 0, },
};


static const uint32_t lastDebounceTime = 0;
static const uint16_t debounceDelay = 20;
static const uint16_t longPressTime = 1000u;
static const uint16_t superLongPressTime = 4000uL;


static inline bool isDebounced(Button_Struct *button){
    uint32_t timePoint = button->pressedTimePoint;
    return (millis() - timePoint) > debounceDelay;
}


static bool buttonReleasedStateMachine(Button_Struct *button){

    bool isStateChanged = false;
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
        isStateChanged = true;
        button->logicState = state;
        Serial.print("Button no:");
        Serial.print(button->pinName, DEC);
        Serial.print(" state:");
        Serial.println(state, DEC);
    }

    return isStateChanged;
}


static bool buttonPressedStateMachine(Button_Struct *button){
    bool isStateChanged = false;
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
        isStateChanged = true;
        button->logicState = state;
        Serial.print("Button no:");
        Serial.print(button->pinName, DEC);
        Serial.print(" state:");
        Serial.println(state, DEC);
    }

    return isStateChanged;
}


    }

}


void buttonTask(void){
    for(uint8_t i=0; i < (sizeof(buttonStateMatrix)/sizeof(buttonStateMatrix[0])); i++){
        Button_Struct * button = &buttonStateMatrix[i];

        bool newPhysState = Gpio_GetPinState(button->pinName);
        if(newPhysState != button->physState){
            button->pressedTimePoint = millis();
            button->physState = newPhysState;
        }

        bool isStateChanged = false;
        if(isDebounced(button)){
            if (button->physState == HIGH) {
                isStateChanged = buttonPressedStateMachine(button);
            }else{
                isStateChanged = buttonReleasedStateMachine(button);
            }
        }
    }
}

