
#if !defined GPIO_H_GUARD
#define GPIO_H_GUARD

#include "stdint.h"
#include "stdbool.h"

typedef enum {
    GPIO_PIN_LED,
    GPIO_PIN_RELAY1,
    GPIO_PIN_RELAY2,
    GPIO_PIN_RELAY3,
    GPIO_PIN_RELAY4,
    GPIO_PIN_BUTTON1,
    GPIO_PIN_BUTTON2,
    GPIO_PIN_BUTTON3,
    GPIO_PIN_BUTTON4,
    GPIO_PIN_BUTTON5,
    GPIO_PIN_BUTTON6,
    GPIO_PIN_BUTTON7,
    GPIO_PIN_PIR8,
    GPIO_PIN_SENTINEL,
} Gpio_Pin;

typedef struct {
    uint8_t pinNumber;
    bool isInput;
    bool isPullUp;
    bool isInvertedLogic;
    bool initState;
} Gpio_Config;

void Gpio_Init(void);
bool Gpio_GetPinState(Gpio_Pin pinName);
void Gpio_SetPinState(Gpio_Pin pinName, bool state);



#endif

