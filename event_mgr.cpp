#include <Arduino.h>
#include "event_mgr.h"
#include "button.h"

//TODO add assert to check matrix size and consistency

//TODO move eventAction to another module
static void enableWallLightA(void){
    Serial.println("enableWallLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
}
static void enableWallLightB(void){
    Serial.println("enableWallLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
}
static void disableWallLightA(void){
    Serial.println("disableWallLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
}
static void disableWallLightB(void){
    Serial.println("disableWallLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
}
static void enableBacklight(void){
    Serial.println("enableWallLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
}
static void timeDisableBacklight(void){
    Serial.println("disableWallLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
}
static void toggleWallLightA(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY1);
    Serial.print("toggleWallLightA:");
    Serial.print("state:");
    Serial.println(state, DEC);
    Gpio_SetPinState(GPIO_PIN_RELAY1, !state);
}
static void toggleWallLightB(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY2);
    Serial.print("toggleWallLightB:");
    Serial.print("state:");
    Serial.println(state, DEC);
    Gpio_SetPinState(GPIO_PIN_RELAY2, !state);
}
static void toggleMainLight(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY3);
    Serial.print("toggleMainLight:");
    Serial.print("state:");
    Serial.println(state, DEC);
    Gpio_SetPinState(GPIO_PIN_RELAY3, !state);
}
static void disableAllLight(void){
    Serial.println("disableAllLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY3, LOW);
}
static void enableAllLight(void){
    Serial.println("enableAllLight");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY3, HIGH);
}
static void disableWallLight(void){
    Serial.println("disableWallLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
}

static void enableWallLight(void){
    Serial.print("enableWallLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
}

EventMgr_Callback  *button1CallbackArray[] = {toggleMainLight,  NULL, disableAllLight,   NULL, enableAllLight,   NULL};
EventMgr_Callback  *button2CallbackArray[] = {toggleWallLightA, NULL, disableWallLightB, NULL, enableWallLightB, NULL};
EventMgr_Callback  *button3CallbackArray[] = {toggleWallLightB, NULL, disableWallLightA, NULL, enableWallLightA, NULL};
EventMgr_Callback  *button4CallbackArray[] = {toggleMainLight,  NULL, disableAllLight,   NULL, enableAllLight,   NULL};
EventMgr_Callback  *button5CallbackArray[] = {toggleMainLight,  NULL, disableAllLight,   NULL, enableAllLight,   NULL};
EventMgr_Callback  *button6CallbackArray[] = {toggleWallLightA, NULL, disableWallLight,  NULL, enableWallLight,  NULL};
EventMgr_Callback  *button7CallbackArray[] = {toggleWallLightB, NULL, disableWallLight,  NULL, enableWallLight,  NULL};
EventMgr_Callback  *pir8CallbackArray[]    = {enableBacklight,  timeDisableBacklight, NULL, NULL, NULL,          NULL};

/*TODO add assert for table size*/
EventMgr_Config eventConfigMatrix[] = {
    [0] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON1, 0, button1CallbackArray, },
    [1] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON2, 0, button2CallbackArray, },
    [2] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON3, 0, button3CallbackArray, },
    [3] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON4, 0, button4CallbackArray, },
    [4] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON5, 0, button5CallbackArray, },
    [5] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON6, 0, button6CallbackArray, },
    [6] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON7, 0, button7CallbackArray, },
    [7] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_PIR8,    0, pir8CallbackArray,    },
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
