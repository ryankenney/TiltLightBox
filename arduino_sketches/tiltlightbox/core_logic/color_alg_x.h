#include "tilt_light_box.h"

#ifndef COLOR_ALG__X_INCLUDED
#define COLOR_ALG__X_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct X_ALG_STATE {
	unsigned long cycleStartTime;
} XAlgState;

/**
 * Initializes the state object for its first use (resetting any timers).
 */
void color_alg_x__init(XAlgState *state);

/**
 * Gets the color for the current time from the specific algorithm assigned
 * to the box. Returns false if no color was found because we've exceeded
 * the duration of the color cycle.
 */
bool color_alg_a__getColor(XAlgState *state, char boxState, unsigned char * result);
bool color_alg_b__getColor(XAlgState *state, char boxState, unsigned char * result);
bool color_alg_c__getColor(XAlgState *state, char boxState, unsigned char * result);
bool color_alg_d__getColor(XAlgState *state, char boxState, unsigned char * result);

#ifdef __cplusplus
}
#endif

#endif
