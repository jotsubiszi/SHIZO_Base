/**
 * Hardware definitions for button config
 */

/** macro guard to avoid duble including */
#if defined(BUTTON_CFG_GUARD)
#error button_cfg included twice!
#else
#define BUTTON_CFG_GUARD
#endif

Button_Struct buttonStateMatrix[/*do not set array size explicitly*/] = {
    {GPIO_PIN_BUTTON1,  BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON2,  BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON3,  BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON4,  BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON5,  BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON6,  BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON7,  BUTTON_STATE_SHORT_RELEASED, false, 0, },
    {GPIO_PIN_BUTTON8,  BUTTON_STATE_SHORT_RELEASED, false, 0, },
};

static const uint32_t lastDebounceTime = 0;
static const uint16_t debounceDelay = 20;
static const uint16_t longPressTime = 1000u;
static const uint32_t superLongPressTime = 2000uL;

