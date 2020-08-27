#include "gpio.h"
#include "button.h"
#include "event_mgr.h"



void setup() {
    Serial.begin(9600);
    Serial.println("\n\n== DEVICE INIT ==");

    Gpio_Init();
    EventMgrInit();
}


void loop() {
    buttonTask();
    EventMgr_CheckEvents();
}

