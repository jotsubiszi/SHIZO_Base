/**
 * Hardware definitions for gpio config
 */

/** macro guard to avoid duble including */
#if defined(GPIO_CFG_GUARD)
#error gpio_cfg included twice!
#else
#define GPIO_CFG_GUARD
#endif

const Gpio_Config gpioHardwareConfigTab[/*do not set array size explicitly (checked by assert)*/] = {
    /*Gpio_Pin        pinNumber isInput isPullup, isInv initState */
    [GPIO_PIN_LED]     = {13,    false,  false,   false,  HIGH},
    [GPIO_PIN_RELAY1]  = {A0,    false,  false,   true,   LOW},
    [GPIO_PIN_RELAY2]  = {A1,    false,  false,   true,   LOW},
    [GPIO_PIN_RELAY3]  = {A2,    false,  false,   true,   LOW},
    [GPIO_PIN_RELAY4]  = {A3,    false,  false,   true,   LOW},
    [GPIO_PIN_BUTTON1] = { 2,    true,   false,   true,  0},
    [GPIO_PIN_BUTTON2] = { 3,    true,   false,   true,  0},
    [GPIO_PIN_BUTTON3] = { 4,    true,   false,   true,  0},
    [GPIO_PIN_BUTTON4] = { 5,    true,   false,   true,  0},
    [GPIO_PIN_BUTTON5] = { 6,    true,   false,   true,  0},
    [GPIO_PIN_BUTTON6] = { 7,    true,   false,   true,  0},
    [GPIO_PIN_BUTTON7] = { 8,    true,   false,   true,  0},
    [GPIO_PIN_BUTTON8] = { 9,    true,   false,   true,  0},
};

