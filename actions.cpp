#include <Arduino.h>
#include "actions.h"
#include "timer.h"
#include "gpio.h"

#define LOGGER_ENABLED 1
#define LOGGER_LEVEL LOG_INFO
#include "logger.h"


void Actions_enableWallLightA(void){
    LOGGERLN(LOG_DEBUG, "enableWallLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
}
void Actions_enableWallLightB(void){
    LOGGERLN(LOG_DEBUG, "enableWallLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
}
void Actions_disableWallLightA(void){
    LOGGERLN(LOG_DEBUG, "disableWallLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
}
void Actions_disableWallLightB(void){
    LOGGERLN(LOG_DEBUG, "disableWallLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
}
void Actions_runBedLightTimer(void){
    LOGGERLN(LOG_DEBUG, "runBedLightTimer:");
    Timer_Run(TIMER_BED_LIGHT);
}
void Actions_enableBedLight(void){
    LOGGERLN(LOG_DEBUG, "enableBedLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY4, HIGH);
    Timer_Stop(TIMER_BED_LIGHT);
    // TODO probably here Timer_Run(TIMER_BED_LIGHT) shall be called
    // to keep light ON when pir is in HIGH state
}
void Actions_disableBedLight(void){
    LOGGERLN(LOG_DEBUG, "disableBedLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY4, LOW);
}
void Actions_toggleWallLightA(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY1);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleWallLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, !state);
}
void Actions_toggleWallLightB(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY2);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleWallLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, !state);
}
void Actions_toggleMainLight(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY3);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleMainLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY3, !state);
}
void Actions_disableAllLight(void){
    LOGGERLN(LOG_DEBUG, "disableAllLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY3, LOW);
}
void Actions_enableAllLight(void){
    LOGGERLN(LOG_DEBUG, "enableAllLight");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY3, HIGH);
}
void Actions_disableWallLight(void){
    LOGGERLN(LOG_DEBUG, "disableWallLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
}

void Actions_enableWallLight(void){
    LOGGER(LOG_DEBUG, "enableWallLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
}

void Actions_toggleLed(void){
    LOGGER(LOG_INFO, "tick!");
    bool state = Gpio_GetPinState(GPIO_PIN_LED);
    Gpio_SetPinState(GPIO_PIN_LED, !state);
}





/* Kitchen & Living room modes */
void Actions_enableLivingLightA(void){
    LOGGERLN(LOG_DEBUG, "enableLivingLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
}
void Actions_enableLivingLightB(void){
    LOGGERLN(LOG_DEBUG, "enableLivingLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
}
void Actions_disableLivingLightA(void){
    LOGGERLN(LOG_DEBUG, "disableLivingLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
}
void Actions_disableLivingLightB(void){
    LOGGERLN(LOG_DEBUG, "disableLivingLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
}
void Actions_enableKitchenLedLight(void){
    LOGGERLN(LOG_DEBUG, "enableKitchenLedLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY4, LOW);
}
void Actions_disableKitchenLedLight(void){
    LOGGERLN(LOG_DEBUG, "disableKitchenLedLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY4, HIGH);
}
void Actions_toggleLivingLightA(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY1);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleLivingLightA:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, !state);
}
void Actions_toggleLivingLightB(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY2);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleLivingLightB:");
    Gpio_SetPinState(GPIO_PIN_RELAY2, !state);
}
void Actions_toggleKitchenLedLight(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY4);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleKitchenLedLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY4, !state);
}
void Actions_toggleKitchenMainLight(void){
    bool state = Gpio_GetPinState(GPIO_PIN_RELAY3);
    LOGGER(LOG_VERBOSE, "state:");
    LOGGERLN(LOG_VERBOSE, state, DEC);
    LOGGER(LOG_DEBUG, " toggleKitchenMainLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY3, !state);
}
void Actions_disableKitchAllLight(void){
    LOGGERLN(LOG_DEBUG, "disableKitchAllLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY3, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY4, LOW);
}
void Actions_enableKitchenAllLight(void){
    LOGGERLN(LOG_DEBUG, "enableKitchenAllLight");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY3, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY4, HIGH);
}
void Actions_disableLivingLight(void){
    LOGGERLN(LOG_DEBUG, "disableLivingLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, LOW);
    Gpio_SetPinState(GPIO_PIN_RELAY2, LOW);
}

void Actions_enableLivingLight(void){
    LOGGER(LOG_DEBUG, "enableLivingLight:");
    Gpio_SetPinState(GPIO_PIN_RELAY1, HIGH);
    Gpio_SetPinState(GPIO_PIN_RELAY2, HIGH);
}

