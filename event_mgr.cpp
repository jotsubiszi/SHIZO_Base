#include <Arduino.h>
#include "event_mgr.h"
#include "button.h"
#include "timer.h"

#define LOGGER_ENABLED 1
#define LOGGER_LEVEL LOG_INFO
#include "logger.h"


//TODO add assert to check matrix size and consistency

//TODO move eventAction to another module
static void enableWallLightA(void){
    LOGGERLN(LOG_DEBUG, "enableWallLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
}
static void enableWallLightB(void){
    LOGGERLN(LOG_DEBUG, "enableWallLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
}
static void disableWallLightA(void){
    LOGGERLN(LOG_DEBUG, "disableWallLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
}
static void disableWallLightB(void){
    LOGGERLN(LOG_DEBUG, "disableWallLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
}
static void runBedLightTimer(void){
    LOGGERLN(LOG_DEBUG, "runBedLightTimer:");
    Timer_Run(TIMER_BED_LIGHT);
}
static void enableBedLight(void){
    LOGGERLN(LOG_DEBUG, "enableBedLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY4, HIGH);
    // TODO probably here Timer_Run(TIMER_BED_LIGHT) shall be called
    // to keep light ON when pir is in HIGH state
}
static void disableBedLight(void){
    LOGGERLN(LOG_DEBUG, "disableBedLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY4, LOW);
}
static void toggleWallLightA(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY1);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleWallLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, !state);
}
static void toggleWallLightB(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY2);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleWallLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, !state);
}
static void toggleMainLight(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY3);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleMainLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY3, !state);
}
static void disableAllLight(void){
    LOGGERLN(LOG_DEBUG, "disableAllLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY3, LOW);
}
static void enableAllLight(void){
    LOGGERLN(LOG_DEBUG, "enableAllLight");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY3, HIGH);
}
static void disableWallLight(void){
    LOGGERLN(LOG_DEBUG, "disableWallLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
}

static void enableWallLight(void){
    LOGGER(LOG_DEBUG, "enableWallLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
}

static void toggleLed(void){
    LOGGER(LOG_INFO, "tick!");
    bool state = Gpio_GetPinState(GPIO_PIN_LED);
    Gpio_SetPinState(GPIO_PIN_LED, !state);
}

EventMgr_Callback  *button1CallbackArray[]  = {toggleMainLight,  NULL, disableAllLight,   NULL, enableAllLight,   NULL};
EventMgr_Callback  *button2CallbackArray[]  = {toggleWallLightA, NULL, disableWallLightB, NULL, enableWallLightB, NULL};
EventMgr_Callback  *button3CallbackArray[]  = {toggleWallLightB, NULL, disableWallLightA, NULL, enableWallLightA, NULL};
EventMgr_Callback  *button4CallbackArray[]  = {toggleMainLight,  NULL, disableAllLight,   NULL, enableAllLight,   NULL};
EventMgr_Callback  *button5CallbackArray[]  = {toggleMainLight,  NULL, disableAllLight,   NULL, enableAllLight,   NULL};
EventMgr_Callback  *button6CallbackArray[]  = {toggleWallLightA, NULL, disableWallLight,  NULL, enableWallLight,  NULL};
EventMgr_Callback  *button7CallbackArray[]  = {toggleWallLightB, NULL, disableWallLight,  NULL, enableWallLight,  NULL};
EventMgr_Callback  *pir8CallbackArray[]     = {NULL, runBedLightTimer, NULL,              NULL, NULL,             NULL};
EventMgr_Callback  *sysResetCallbackArray[] = {NULL, NULL, NULL, toggleLed, toggleLed,};
EventMgr_Callback  *bedLightCallbackArray[] = {NULL, enableBedLight, disableBedLight, NULL, NULL,};

/*TODO add assert for table size*/
EventMgr_Config eventConfigMatrix[] = {
    [0] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON1, 0, button1CallbackArray,  },
    [1] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON2, 0, button2CallbackArray,  },
    [2] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON3, 0, button3CallbackArray,  },
    [3] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON4, 0, button4CallbackArray,  },
    [4] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON5, 0, button5CallbackArray,  },
    [5] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON6, 0, button6CallbackArray,  },
    [6] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON7, 0, button7CallbackArray,  },
    [7] = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_PIR8,    0, pir8CallbackArray,     },
    [8] = {EVENT_TYPE_TIMER,  0, NULL, TIMER_SYS_RUN,    0, sysResetCallbackArray, },
    [9] = {EVENT_TYPE_TIMER,  0, NULL, TIMER_BED_LIGHT,  0, bedLightCallbackArray, },
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

static EventMgr_Callback* isTimerEventOccured(EventMgr_Config *event){
    EventMgr_Callback *eventCallback = NULL;

    Timer_Struct *timerObj = (Timer_Struct *)event->object;
    Timer_State oldEventState = (Timer_State)event->oldState;
    Timer_State eventState = timerObj->state;

    if(eventState != oldEventState){
        eventCallback = (EventMgr_Callback *)event->callbacks[eventState];
        event->oldState = eventState;
    }

    return eventCallback;
}

void EventMgrInit(void){
    for(uint8_t i=0; i < (sizeof(eventConfigMatrix)/sizeof(eventConfigMatrix[0])); i++){
        EventMgr_Config * event = &eventConfigMatrix[i];
        uint8_t objectIndex;

        switch(event->type){
            case EVENT_TYPE_BUTTON:
                objectIndex = (uint8_t)event->objectIndex;
                event->object = (void*)Button_FindHandler((Gpio_Pin)objectIndex);
                break;

            case EVENT_TYPE_TIMER:
                objectIndex = (uint8_t)event->objectIndex;
                event->object = (void*)Timer_FindHandler((Timer_Name)objectIndex);
                break;

            case EVENT_TYPE_SENTINEL:
            default:
                //TODO assert here
                break;
        }
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
            LOGGERLN(LOG_INFO, "event callback");
            eventCallback();
        }
    }
}

