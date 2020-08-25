
#if !defined GPIO_H_GUARD
#define GPIO_H_GUARD

#include "stdint.h"
#include "stdbool.h"

typedef enum {
    GPIO_PIN_LED,
    GPIO_PIN_RELAY,
    GPIO_PIN_BUTTON,
    GPIO_PIN_SENTINEL,
} Gpio_Pin;

typedef struct {
    uint8_t pinNumber;
    bool isInput;
    bool isInvertedLogic;
    bool initState;
} Gpio_Config;

void Gpio_Init(void);
bool Gpio_GetPinState(Gpio_Pin pinName);



#endif

