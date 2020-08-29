#include "gpio.h"
#include <Arduino.h>
#include <Arduino.h>
#include <assert.h>

const Gpio_Config gpioHardwareConfigTab[/*do not set array size explicitly (checked by assert)*/] = {
    [GPIO_PIN_LED]     = {13, false, false, HIGH},
    [GPIO_PIN_RELAY1]  = {10, false, true,  LOW},
    [GPIO_PIN_RELAY2]  = { 9, false, true,  LOW},
    [GPIO_PIN_RELAY3]  = { 8, false, true,  LOW},
    [GPIO_PIN_RELAY4]  = { 7, false, true,  LOW},
    [GPIO_PIN_BUTTON1] = { 6, true,  false, 0},
    [GPIO_PIN_BUTTON2] = { 5, true,  false, 0},
    [GPIO_PIN_BUTTON3] = { 4, true,  false, 0},
    [GPIO_PIN_BUTTON4] = { 3, true,  false, 0},
    [GPIO_PIN_BUTTON5] = { 2, true,  false, 0},
    [GPIO_PIN_BUTTON6] = {A0, true,  false, 0},
    [GPIO_PIN_BUTTON7] = {A1, true,  false, 0},
    [GPIO_PIN_PIR8] =    {A2, true,  false, 0},
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
    bool isInvLogic = gpioHardwareConfigTab[pinName].isInvertedLogic;
    bool state = digitalRead(pinNo);
    return isInvLogic ? !state : state;
}

void Gpio_SetPinState(Gpio_Pin pinName, bool state){
    //TODO add assert

    uint8_t pinNo = gpioHardwareConfigTab[pinName].pinNumber;
    bool isInvLogic = gpioHardwareConfigTab[pinName].isInvertedLogic;
    bool physicState = isInvLogic ? !state : state;
    digitalWrite(pinNo, physicState);
}

