/**
 * Hardware definitions of event_mgr for kitchen
 */

/** macro guard to avoid double including */
#if defined(EVENT_MGR_CFG_GUARD)
#error event_mgr_cfg included twice!
#else
#define EVENT_MGR_CFG_GUARD
#endif

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

