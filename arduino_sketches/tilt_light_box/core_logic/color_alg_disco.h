#include "tilt_light_box.h"

#ifndef COLOR_ALG__DISCO_INCLUDED
#define COLOR_ALG__DISCO_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DISCO_ALG_STATE {
	unsigned long cycleStartTime;
} DiscoAlgState;

/**
 * Initializes the state object for its first use (resetting any timers).
 */
void color_alg_disco__init(DiscoAlgState *state);

/**
 * Gets the color for the current time from the specific algorithm assigned
 * to the box. Returns false if no color was found because we've exceeded
 * the duration of the color cycle.
 */
bool color_alg_disco__getColor(DiscoAlgState *state, char boxState, unsigned char * result);

#ifdef __cplusplus
}
#endif

#endif
