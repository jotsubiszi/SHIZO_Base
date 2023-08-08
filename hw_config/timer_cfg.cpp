/**
 * Hardware definitions for timer config
 */

/** macro guard to avoid duble including */
#if defined(TIMER_CFG_GUARD)
#error timer_cfg included twice!
#else
#define TIMER_CFG_GUARD
#endif

//TODO add table consistency assert
//TODO pass as parameter at timer_create
//TODO assert timeout < MAX_INT32
Timer_Struct timerStateMatrix[/*do not set array size explicitly*/] = {
    [TIMER_SYS_RUN] =   {TIMER_STOPPED, true,  0, 500uL},
    [TIMER_BED_LIGHT] = {TIMER_STOPPED, false, 0, SEC_TO_MS(10uL)},
};

