#include "color_generator.h"

#ifndef COLOR_ALG__PURPLE_CALM_INCLUDED
#define COLOR_ALG__PURPLE_CALM_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PURPLE_CALM_ALG_STATE {
	unsigned long cycleStartTime;
} PurpleCalmAlgState;

/**
 * Initializes the state object for its first use (resetting any timers).
 */
void color_alg_purple_calm__init(PurpleCalmAlgState *state);

void color_alg_purple_calm__getColor(PurpleCalmAlgState *state, char boxState, unsigned char * result);

#ifdef __cplusplus
}
#endif

#endif