#include "gpio.h"
#include "button.h"
#include "timer.h"
#include "event_mgr.h"


#define LOGGER_ENABLED 1
#define LOGGER_LEVEL LOG_INFO
#include "logger.h"


void setup() {
    Serial.begin(9600);
    LOGGERLN(LOG_INFO, "\n\n== DEVICE INIT ==");

    Gpio_Init();
    EventMgrInit();
    Timer_Run(TIMER_SYS_RUN);
}


void loop() {
    buttonTask();
    EventMgr_CheckEvents();
    Timer_TaskMain();
}

