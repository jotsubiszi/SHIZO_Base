
#if !defined EVENT_MGR_H_GUARD
#define EVENT_MGR_H_GUARD

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    EVENT_TYPE_BUTTON,
    EVENT_TYPE_TIMER,
    EVENT_TYPE_SENTINEL,
} EventMgr_Type;

typedef void (EventMgr_Callback)(void);

typedef struct {
    EventMgr_Type type;
    int8_t counter;
    void *object;
    uint8_t objectIndex;
    uint8_t oldState;
    EventMgr_Callback **callbacks;
} EventMgr_Config;

void EventMgrInit(void);
void EventMgr_CheckEvents(void);


#endif


