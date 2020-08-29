#include <Arduino.h>
#include "event_mgr.h"
#include "button.h"

//TODO add assert to check matrix size and consistency

//TODO move eventAction to another module
static void toggleRelay1(void){
    static uint8_t i;
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY1);
        Serial.print("toggleRelay1:");
        Serial.println(i++, DEC);
        Serial.print("state:");
        Serial.println(state, DEC);
        Gpio_SetPinState(GPIO_PIN_RELAY1, !state);
}
static void toggleRelay2(void){
    static uint8_t i;
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY2);
        Serial.print("toggleRelay2:");
        Serial.println(i++, DEC);
        Gpio_SetPinState(GPIO_PIN_RELAY2, !state);
}
static void toggleRelay3(void){
    static uint8_t i;
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY3);
        Serial.print("toggleRelay3:");
        Serial.println(i++, DEC);
        Gpio_SetPinState(GPIO_PIN_RELAY3, !state);
}
static void toggleRelay4(void){
    static uint8_t i;
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY4);
        Serial.print("toggleRelay4:");
        Serial.println(i++, DEC);
        Gpio_SetPinState(GPIO_PIN_RELAY4, !state);
}
static void toggleRelay5(void){
    static uint8_t i;
    bool state1 = Gpio_GetPinState(GPIO_PIN_RELAY1);
    bool state2 = Gpio_GetPinState(GPIO_PIN_RELAY2);
        Serial.print("toggleRelay  1 and 2:");
        Serial.println(i++, DEC);
        Gpio_SetPinState(GPIO_PIN_RELAY1, !state1);
        Gpio_SetPinState(GPIO_PIN_RELAY2, !state2);
}
static void toggleAllRelay(void){
    static uint8_t i;
    bool state1 = Gpio_GetPinState(GPIO_PIN_RELAY1);
    bool state2 = Gpio_GetPinState(GPIO_PIN_RELAY2);
    bool state3 = Gpio_GetPinState(GPIO_PIN_RELAY3);
    bool state4 = Gpio_GetPinState(GPIO_PIN_RELAY4);
        Serial.print("toggleAllRelay:");
        Serial.println(i++, DEC);
        Gpio_SetPinState(GPIO_PIN_RELAY1, !state1);
        Gpio_SetPinState(GPIO_PIN_RELAY2, !state2);
        Gpio_SetPinState(GPIO_PIN_RELAY3, !state3);
        Gpio_SetPinState(GPIO_PIN_RELAY4, !state4);
}

static void disableAllRelay(void){
    static uint8_t i;
        Serial.print("disableAllRelay:");
        Serial.println(i++, DEC);
        Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
        Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
        Gpio_SetPinState(GPIO_PIN_RELAY3, LOW);
        Gpio_SetPinState(GPIO_PIN_RELAY4, LOW);
}

EventMgr_Callback  *button1CallbackArray[] = {toggleRelay1, NULL, toggleAllRelay, NULL, disableAllRelay, NULL};
EventMgr_Callback  *button2CallbackArray[] = {toggleRelay2, NULL, toggleAllRelay, NULL, disableAllRelay, NULL};
EventMgr_Callback  *button3CallbackArray[] = {toggleRelay3, NULL, toggleAllRelay, NULL, disableAllRelay, NULL};
EventMgr_Callback  *button4CallbackArray[] = {toggleRelay4, NULL, toggleAllRelay, NULL, disableAllRelay, NULL};
EventMgr_Callback  *button5CallbackArray[] = {toggleRelay5, NULL, toggleAllRelay, NULL, disableAllRelay, NULL};

/*TODO add assert for table size*/
EventMgr_Config eventConfigMatrix[] = {
    [0] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON1, 0, button1CallbackArray, },
    [1] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON2, 0, button2CallbackArray, },
    [2] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON3, 0, button3CallbackArray, },
    [3] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON4, 0, button4CallbackArray, },
    [4] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON5, 0, button5CallbackArray, },
};

static EventMgr_Callback* isButtonEventOccured(EventMgr_Config *event){
    EventMgr_Callback *eventCallback = NULL;

    Button_Struct *buttonObj = (Button_Struct *)event->object;
    Button_State oldEventState = (Button_State)event->oldState;
    Button_State eventState = buttonObj->logicState;

    if(eventState != oldEventState){
        eventCallback = (EventMgr_Callback *)event->callbacks[eventState];
        event->oldState = eventState;
    }
    return eventCallback;
}

static EventMgr_Callback* isTimerEventOccured(void *event){
    //TODO dummy function as yet
    return NULL;

}

void EventMgrInit(void){
    for(uint8_t i=0; i < (sizeof(eventConfigMatrix)/sizeof(eventConfigMatrix[0])); i++){
        EventMgr_Config * event = &eventConfigMatrix[i];

        uint8_t objectIndex = (uint8_t)event->objectIndex;
        event->object = (void*)Button_FindHandler((Gpio_Pin)objectIndex);
        //TODO add TIMER object finder
    }
}

void EventMgr_CheckEvents(void){
    //TODO assert if not initialized
    for(uint8_t i=0; i<(sizeof(eventConfigMatrix)/sizeof(eventConfigMatrix[0])); i++){
        EventMgr_Callback *eventCallback = NULL;
        EventMgr_Config *event = &eventConfigMatrix[i];

        switch(event->type){

            case EVENT_TYPE_BUTTON:
                eventCallback = isButtonEventOccured(event);
                break;

            case EVENT_TYPE_TIMER:
                eventCallback = isTimerEventOccured(event);
                break;

            case EVENT_TYPE_SENTINEL:
            default:
                break;
                //todo assert here
        }

        if(eventCallback != NULL){
            event->counter++;
            Serial.println("event callback call");
            eventCallback();
        }
    }
}

void executeEventCallbacks(void){

}
