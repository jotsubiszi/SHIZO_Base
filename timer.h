#include "stdint.h"
#include "stdbool.h"

#if !defined TIMER_H_GUARD
#define TIMER_H_GUARD


#define SEC_TO_MS(T) ((T)*1000uL)
#define MIN_TO_MS(T) ((T)*1000uL*60uL)
#define HOUR_TO_MS(T) ((T)*1000uL*60uL*60uL)

typedef enum {
    TIMER_SYS_RUN,
    TIMER_BED_LIGHT,
    TIMER_NAME_SENTINEL,
} Timer_Name;

typedef enum {
    TIMER_STOPPED,
    TIMER_RUNNING,
    TIMER_EXPIRED,
    TIMER_EXPIRED_PERIOD_A, //< Expired Period A and B used to indicate next period
    TIMER_EXPIRED_PERIOD_B,
    TIMER_SENTINEL,
} Timer_State;


typedef void (*Timer_Callback)(void);


typedef struct{
    Timer_State state;
    const bool isPeriodic;
    uint32_t startingTime;
    const int32_t timeout;
} Timer_Struct;


void Timer_TaskMain(void);
Timer_Struct *Timer_FindHandler(Timer_Name timerName);
void Timer_Stop(Timer_Name timerName);
void Timer_Run(Timer_Name timerName);

#endif
