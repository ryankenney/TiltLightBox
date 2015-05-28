#include "color_generator.h"

#ifndef COLOR_ALG_PURPLE_CALM_INCLUDED
#define COLOR_ALG_PURPLE_CALM_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PURPLE_CALM_ALG_STATE {
	char currentPhase;
	unsigned long cycleStartTime;
} PurpleCalmAlgState;

void color_alg_purple_calm__init(PurpleCalmAlgState *state);

void color_alg_purple_calm__getColor(PurpleCalmAlgState *state, unsigned char * result);

#ifdef __cplusplus
}
#endif

#endif