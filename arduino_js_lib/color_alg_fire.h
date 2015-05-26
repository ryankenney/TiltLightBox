#include "color_generator.h"

#ifndef COLOR_ALG_FIRE_INCLUDED
#define COLOR_ALG_FIRE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FIRE_ALG_STATE {
	unsigned long cycleStartTime;
} FireAlgState;

void color_alg_fire_init(FireAlgState *state);

void color_alg_fire_getColor(FireAlgState *state, unsigned char *);

#ifdef __cplusplus
}
#endif

#endif