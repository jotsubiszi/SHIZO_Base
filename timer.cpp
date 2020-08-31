#include "Arduino.h"
#include "timer.h"

//TODO add table consistency assert
//TODO pass as parameter at timer_create
//TODO assert timeout < MAX_INT32
Timer_Struct timerStateMatrix[] = {
    [TIMER_SYS_RUN] =   {TIMER_STOPPED, true,  0, 500uL},
    [TIMER_BED_LIGHT] = {TIMER_STOPPED, false, 0, SEC_TO_MS(4uL)},
};


void timeoutDetected(Timer_Struct *timer){
    if(timer->isPeriodic){
        /* calculate the starting point 'as it should be' based on the old starting point
         * it helps to avoid an error accumulation on each timer refreshing*/
        timer->startingTime = timer->startingTime + timer->timeout;
        Serial.print("now: ");
        Serial.print(millis(), DEC);
        Serial.print("next: ");
        Serial.print(millis()+timer->timeout, DEC);
        Serial.print("periodic ");
    }
    Serial.print("timer expired: ");
    Serial.println(timer->timeout, DEC);

    switch(timer->state){
        case TIMER_RUNNING:
            timer->state = TIMER_EXPIRED;
            break;

        case TIMER_EXPIRED_PERIOD_A:
            timer->state = TIMER_EXPIRED_PERIOD_B;
            break;

        case TIMER_EXPIRED_PERIOD_B:
            timer->state = TIMER_EXPIRED_PERIOD_A;
            break;

        case TIMER_STOPPED:
        case TIMER_EXPIRED:
        case TIMER_SENTINEL:
        default:
            //TODO add assert
            break;
    }
}


static int32_t getTickDiff(uint32_t a, uint32_t b){
    return (int32_t)a - b;
}


static void isTimerExpired(Timer_Struct *timer){
    int32_t passedTime = getTickDiff(millis(), timer->startingTime);

    /* it handle time rollover */
    if(passedTime > timer->timeout){
        timeoutDetected(timer);
    }
}


void Timer_TaskMain(void){
    for(uint8_t i=0; i < (sizeof(timerStateMatrix)/sizeof(timerStateMatrix[0])); i++){
        Timer_Struct * timer = &timerStateMatrix[i];

        switch(timer->state){
        case TIMER_STOPPED:
        case TIMER_EXPIRED:
            /* do nothing */
            break;

        case TIMER_RUNNING:
        case TIMER_EXPIRED_PERIOD_A:
        case TIMER_EXPIRED_PERIOD_B:
            isTimerExpired(timer);
            break;

        case TIMER_SENTINEL:
        default:
            //TODO add assert
            break;
        }
    }
}

Timer_Struct *Timer_FindHandler(Timer_Name timerName){
    return &timerStateMatrix[timerName];
}


void Timer_Run(Timer_Name timerName){
    Serial.print("run timer:");
    Serial.println(timerName, DEC);

    Timer_Struct * timer = &timerStateMatrix[timerName];
    timer->state = TIMER_RUNNING;
    timer->startingTime = millis();
}


void Timer_Stop(Timer_Name timerName){
    Serial.print("stop timer:");
    Serial.println(timerName, DEC);

    Timer_Struct * timer = &timerStateMatrix[timerName];
    timer->state = TIMER_STOPPED;
}
