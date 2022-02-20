#include "gpio.h"
#include <Arduino.h>
#include <Arduino.h>
#include <assert.h>

#define LOGGER_ENABLED 1
#define LOGGER_LEVEL LOG_INFO
#include "logger.h"

/* ugly source include since Arduino does not support source/config directories */
#include "hw_config/gpio_cfg.cpp"


static_assert((sizeof(gpioHardwareConfigTab)/sizeof(gpioHardwareConfigTab[0])) == GPIO_PIN_SENTINEL);

static void configureInput(const Gpio_Config *config){
    uint8_t pin = config->pinNumber;
    bool isPullUp = config->isPullUp;


    if(isPullUp){
        pinMode(pin, INPUT_PULLUP);
        LOGGER(LOG_DEBUG, "pullup ");
    }else{
        pinMode(pin, INPUT);
    }

    LOGGER(LOG_DEBUG, "input ");
}


static void configureOutput(const Gpio_Config *config){
    uint8_t pin = config->pinNumber;
    bool isInvLogic = config->isInvertedLogic;
    bool initState = config->initState;

    LOGGER(LOG_DEBUG, "output ");
    LOGGER(LOG_DEBUG, " initState:");

    if(isInvLogic){
        digitalWrite(pin, initState ? LOW : HIGH);
        LOGGER(LOG_DEBUG, initState ? LOW : HIGH, DEC);
    } else {
        digitalWrite(pin, initState ? HIGH : LOW);
        LOGGER(LOG_DEBUG, initState ? HIGH : LOW, DEC);
    }

    pinMode(pin, OUTPUT);
}


void Gpio_Init(void){
    LOGGERLN(LOG_INFO, "Gpio Init");

    for(uint8_t i=0; i < (sizeof(gpioHardwareConfigTab)/sizeof(gpioHardwareConfigTab[0])); i++){
        const Gpio_Config *pinHandler = &gpioHardwareConfigTab[i];

        LOGGER(LOG_DEBUG, "pin:");
        LOGGER(LOG_DEBUG, pinHandler->pinNumber, DEC);
        LOGGER(LOG_DEBUG, " = ");
        LOGGER(LOG_DEBUG, pinHandler->isInput, DEC);

        if(pinHandler->isInput){
            configureInput(pinHandler);
        }else{
            configureOutput(pinHandler);
        }

        LOGGERLN(LOG_DEBUG, "");
    }
}


bool Gpio_GetPinState(Gpio_Pin pinName){
    //TODO add assert

    uint8_t pinNo = gpioHardwareConfigTab[pinName].pinNumber;
    bool isInvLogic = gpioHardwareConfigTab[pinName].isInvertedLogic;

    bool state = digitalRead(pinNo);
    return isInvLogic ? !state : state;
}


void Gpio_SetPinState(Gpio_Pin pinName, bool state){
    //TODO add assert
    LOGGER(LOG_DEBUG, "gpio:");
    LOGGER(LOG_DEBUG, pinName, DEC);
    LOGGER(LOG_DEBUG, " set:");
    LOGGERLN(LOG_DEBUG, state, DEC);

    uint8_t pinNo = gpioHardwareConfigTab[pinName].pinNumber;
    bool isInvLogic = gpioHardwareConfigTab[pinName].isInvertedLogic;
    bool physicState = isInvLogic ? !state : state;

    digitalWrite(pinNo, physicState);

}

