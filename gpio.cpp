#include "gpio.h"
#include <Arduino.h>
#include <Arduino.h>
#include <assert.h>

const Gpio_Config gpioHardwareConfigTab[/*do not set array size explicitly (checked by assert)*/] = {
    [GPIO_PIN_LED]      = {13, false, false, HIGH},
    [GPIO_PIN_RELAY]    = {12, false, false, LOW},
    [GPIO_PIN_BUTTON]   = {8,  true,  false, 0},
};

//TODO add normal assert macro
static void asserTests(void){
    uint8_t isOk=true;

    /*is gpioHardwareConfigTab completely populated */
    if((sizeof(gpioHardwareConfigTab)/sizeof(gpioHardwareConfigTab[0])) != GPIO_PIN_SENTINEL) { isOk=false; }


    if( !isOk){
        Serial.println("== ASSERT HALT ==");

        /*stay here if assert fail*/
        for(;;){}
    }
        Serial.println("ASSERT OK");
}

void Gpio_Init(void){
    Serial.println("Gpio Init");

    asserTests();

    for(uint8_t i=0; i < (sizeof(gpioHardwareConfigTab)/sizeof(gpioHardwareConfigTab[0])); i++){
        uint8_t pin = gpioHardwareConfigTab[i].pinNumber;
        bool isInput = gpioHardwareConfigTab[i].isInput;

        Serial.print("pin:");
        Serial.print(pin, DEC);
        Serial.print(" = ");
        Serial.print(isInput, DEC);

        if(isInput){
            pinMode(pin, INPUT);
            Serial.print("input ");
        }else{
            pinMode(pin, OUTPUT);
            Serial.print("output ");
            bool isInvLogic = gpioHardwareConfigTab[i].isInvertedLogic;
            bool initState = gpioHardwareConfigTab[i].initState;

            Serial.print(" initState:");
            if(isInvLogic){
                digitalWrite(pin, initState ? LOW : HIGH);
                Serial.print(initState ? LOW : HIGH, DEC);
            } else {
                digitalWrite(pin, initState ? HIGH : LOW);
                Serial.print(initState ? HIGH : LOW, DEC);
            }
        }
        Serial.println("");
    }
}

bool Gpio_GetPinState(Gpio_Pin pinName){
    //TODO add assert

    uint8_t pinNo = gpioHardwareConfigTab[pinName].pinNumber;
    bool state = digitalRead(pinNo);
#if defined(DEBUG) && (DEBUG == 1)
    Serial.print("pinName:");
    Serial.print(pinName, DEC);
    Serial.print(" pinNo:");
    Serial.print(pinNo, DEC);
    Serial.print(" state:");
    Serial.println(state, DEC);
#endif
    return state;
}



