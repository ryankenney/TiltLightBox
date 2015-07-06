#include "tilt_light_box.h"

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

/**
 * Gets the color for the current time from the specific algorithm assigned
 * to the box. Returns false if no color was found because we've exceeded
 * the duration of the color cycle.
 */
bool color_alg_purple_calm__getColor(PurpleCalmAlgState *state, char boxState, unsigned char * result);

#ifdef __cplusplus
}
#endif

#endif
