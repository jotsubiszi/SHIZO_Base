/**
 * Project config picker for event_mgr
 * TODO do board configuration in a proper manner
 */

#include "global_cfg.h"

/* project must be defined first */
#if (!defined(PROJECT) || !defined(KITCHEN) || !defined(BEDROOM) || (BEDROOM == KITCHEN))
#error project deifnition error!
#endif


#if PROJECT == KITCHEN
/* ugly source include since Arduino does not support source/config directories */
#include "kitchen/event_mgr_cfg.cpp"

#elif PROJECT == BEDROOM
/* ugly source include since Arduino does not support source/config directories */
#include "bedroom/event_mgr_cfg.cpp"


#else
#error project deifnition error!

#endif

