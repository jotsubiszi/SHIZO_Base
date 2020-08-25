#include "gpio.h"
void setup() {
    Serial.begin(9600);
    Serial.println("\n\n== DEVICE INIT ==");

    Gpio_Init();
}


void loop() {
}

