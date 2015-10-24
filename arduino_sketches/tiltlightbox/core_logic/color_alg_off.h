#include "tilt_light_box.h"

#ifndef COLOR_ALG__OFF_INCLUDED
#define COLOR_ALG__OFF_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OFF_ALG_STATE {
	unsigned long cycleStartTime;
} OffAlgState;

/**
 * Initializes the state object for its first use (resetting any timers).
 */
void color_alg_off__init(OffAlgState *state);

/**
 * Gets the color for the current time from the specific algorithm assigned
 * to the box. Returns false if no color was found because we've exceeded
 * the duration of the color cycle.
 */
bool color_alg_off__getColor(OffAlgState *state, char boxState, unsigned char * result);

#ifdef __cplusplus
}
#endif

#endif
