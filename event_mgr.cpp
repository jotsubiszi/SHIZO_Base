#include <Arduino.h>
#include "event_mgr.h"
#include "button.h"
#include "timer.h"
#include "actions.h"

#define LOGGER_ENABLED 1
#define LOGGER_LEVEL LOG_INFO
#include "logger.h"

/* ugly source include since Arduino does not support source/config directories */
#include "hw_config/event_mgr_cfg.cpp"

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

