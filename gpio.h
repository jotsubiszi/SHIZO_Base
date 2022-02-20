
#if !defined GPIO_H_GUARD
#define GPIO_H_GUARD

#include "stdint.h"
#include "stdbool.h"
#include "hw_config/gpio_cfg.h"

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

