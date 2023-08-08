
#if !defined ACTIONS_H_GUARD
#define ACTIONS_MGR_H_GUARD

#include <stdint.h>
#include <stdbool.h>

typedef void (Action_Callback)(void);

void Actions_enableWallLightA(void);
void Actions_enableWallLightB(void);
void Actions_disableWallLightA(void);
void Actions_disableWallLightB(void);
void Actions_runBedLightTimer(void);
void Actions_enableBedLight(void);
void Actions_disableBedLight(void);
void Actions_toggleWallLightA(void);
void Actions_toggleWallLightB(void);
void Actions_toggleMainLight(void);
void Actions_disableAllLight(void);
void Actions_enableAllLight(void);
void Actions_disableWallLight(void);
void Actions_enableWallLight(void);
void Actions_toggleLed(void);


void Actions_enableLivingLightA(void);
void Actions_enableLivingLightB(void);
void Actions_disableLivingLightA(void);
void Actions_disableLivingLightB(void);
void Actions_enableKitchenLedLight(void);
void Actions_disableKitchenLedLight(void);
void Actions_toggleLivingLightA(void);
void Actions_toggleLivingLightB(void);
void Actions_toggleKitchenLedLight(void);
void Actions_toggleKitchenMainLight(void);
void Actions_disableKitchAllLight(void);
void Actions_enableKitchenAllLight(void);
void Actions_disableLivingLight(void);
void Actions_enableLivingLight(void);

#endif

