#include <Arduino.h>
#include "event_mgr.h"
#include "button.h"
#include "timer.h"
#include "actions.h"

#define LOGGER_ENABLED 1
#define LOGGER_LEVEL LOG_INFO
#include "logger.h"

/* TODO move project dependent file (config) to another .c or .h files */
#define KITCHEN 1

#if (defined(KITCHED) && defined(BEDROOOM)) || (!defined(KITCHEN) && !defined(BEDROOM))
#error project deifnition error
#endif

#if (KITCHEN == 1)
const Action_Callback  *button1CallbackArray[]  = {Actions_toggleKitchenMainLight,    NULL, Actions_disableKitchAllLight,  NULL, Actions_enableKitchenAllLight,   NULL};
const Action_Callback  *button2CallbackArray[]  = {Actions_toggleKitchenLedLight,     NULL, Actions_disableKitchAllLight,  NULL, Actions_enableKitchenAllLight,   NULL};
const Action_Callback  *button3CallbackArray[]  = {Actions_toggleKitchenMainLight,    NULL, Actions_disableKitchAllLight,  NULL, Actions_enableKitchenAllLight,   NULL};
const Action_Callback  *button4CallbackArray[]  = {Actions_toggleKitchenLedLight,     NULL, Actions_disableKitchAllLight,  NULL, Actions_enableKitchenAllLight,   NULL};
const Action_Callback  *button5CallbackArray[]  = {Actions_toggleKitchenMainLight,    NULL, Actions_disableKitchAllLight,  NULL, Actions_enableKitchenAllLight,   NULL};
const Action_Callback  *button6CallbackArray[]  = {Actions_toggleKitchenLedLight,     NULL, Actions_disableKitchAllLight,  NULL, Actions_enableKitchenAllLight,   NULL};
const Action_Callback  *button7CallbackArray[]  = {Actions_toggleLivingLightA,        NULL, Actions_disableKitchAllLight,  NULL, Actions_enableKitchenAllLight,   NULL};
const Action_Callback  *button8CallbackArray[]  = {Actions_toggleLivingLightB,        NULL, Actions_disableKitchAllLight,  NULL, Actions_enableKitchenAllLight,   NULL};
const Action_Callback  *sysResetCallbackArray[] = {NULL, NULL, NULL, Actions_toggleLed, Actions_toggleLed,};
const Action_Callback  *bedLightCallbackArray[] = {NULL, Actions_enableKitchenLedLight, Actions_disableKitchenLedLight, NULL, NULL,};
#elif (BEDROOM == 1)
const Action_Callback  *button1CallbackArray[]  = {Actions_toggleMainLight,  NULL, Actions_disableAllLight,   NULL, Actions_enableAllLight,   NULL};
const Action_Callback  *button2CallbackArray[]  = {Actions_toggleWallLightA, NULL, Actions_disableWallLightB, NULL, Actions_enableWallLightB, NULL};
const Action_Callback  *button3CallbackArray[]  = {Actions_toggleWallLightB, NULL, Actions_disableWallLightA, NULL, Actions_enableWallLightA, NULL};
const Action_Callback  *button4CallbackArray[]  = {Actions_toggleMainLight,  NULL, Actions_disableAllLight,   NULL, Actions_enableAllLight,   NULL};
const Action_Callback  *button5CallbackArray[]  = {Actions_toggleMainLight,  NULL, Actions_disableAllLight,   NULL, Actions_enableAllLight,   NULL};
const Action_Callback  *button6CallbackArray[]  = {Actions_toggleWallLightA, NULL, Actions_disableWallLight,  NULL, Actions_enableWallLight,  NULL};
const Action_Callback  *button7CallbackArray[]  = {Actions_toggleWallLightB, NULL, Actions_disableWallLight,  NULL, Actions_enableWallLight,  NULL};
const Action_Callback  *pir8CallbackArray[]     = {NULL, Actions_runBedLightTimer, NULL,              NULL, NULL,             NULL};
const Action_Callback  *sysResetCallbackArray[] = {NULL, NULL, NULL, Actions_toggleLed, Actions_toggleLed,};
const Action_Callback  *bedLightCallbackArray[] = {NULL, Actions_enableBedLight, Actions_disableBedLight, NULL, NULL,};
#else
#error define project!
#endif

/*TODO add assert for table size*/
EventMgr_Config eventConfigMatrix[] = {
    [0]  = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON1,  0, button1CallbackArray,  },
    [1]  = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON2,  0, button2CallbackArray,  },
    [2]  = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON3,  0, button3CallbackArray,  },
    [3]  = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON4,  0, button4CallbackArray,  },
    [4]  = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON5,  0, button5CallbackArray,  },
    [5]  = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON6,  0, button6CallbackArray,  },
    [6]  = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON7,  0, button7CallbackArray,  },
    [7]  = {EVENT_TYPE_BUTTON, 0, NULL, GPIO_PIN_BUTTON8,  0, button8CallbackArray,  },
    [8] = {EVENT_TYPE_TIMER,  0, NULL, TIMER_SYS_RUN,     0, sysResetCallbackArray, },
    [9] = {EVENT_TYPE_TIMER,  0, NULL, TIMER_BED_LIGHT,   0, bedLightCallbackArray, },
};

static Action_Callback* isButtonEventOccured(EventMgr_Config *event){
    Action_Callback *eventCallback = NULL;

    Button_Struct *buttonObj = (Button_Struct *)event->object;
    Button_State oldEventState = (Button_State)event->oldState;
    Button_State eventState = buttonObj->logicState;

    if(eventState != oldEventState){
        eventCallback = (Action_Callback *)event->callbacks[eventState];
        event->oldState = eventState;
    }

    return eventCallback;
}

static Action_Callback* isTimerEventOccured(EventMgr_Config *event){
    Action_Callback *eventCallback = NULL;

    Timer_Struct *timerObj = (Timer_Struct *)event->object;
    Timer_State oldEventState = (Timer_State)event->oldState;
    Timer_State eventState = timerObj->state;

    if(eventState != oldEventState){
        eventCallback = (Action_Callback *)event->callbacks[eventState];
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
        Action_Callback *eventCallback = NULL;
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

