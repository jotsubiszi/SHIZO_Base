#include "gpio.h"
#include "button.h"
#include "timer.h"
#include "event_mgr.h"



void setup() {
    Serial.begin(9600);
    Serial.println("\n\n== DEVICE INIT ==");

    Gpio_Init();
    EventMgrInit();
    Timer_Run(TIMER_SYS_RUN);
}


void loop() {
    buttonTask();
    EventMgr_CheckEvents();
    Timer_TaskMain();
}

