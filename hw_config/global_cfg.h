#if !defined GLOBAL_CFG_H_GUARD
#define GLOBAL_CFG_H_GUARD


/* TODO things that should be handled by buildsystem */
#define KITCHEN 1
#define BEDROOM 2

/* weak Project definition */
#if !(defined PROJECT)
#define PROJECT KITCHEN
#endif


#endif

