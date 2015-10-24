#include "tilt_light_box.h"

// ==== Private =====

ColorPhase color_alg_disco__phasesUpright[] =  {
	{{255,100,0},{192,192,192},5000},
	{{192,192,192},{255,100,0},5000},
};

ColorPhase color_alg_disco__phasesTilting[] =  {
	{{0,0,0},{0,0,0},100},
	{{255,255,255},{255,255,255},100},
	{{0,0,0},{0,0,0},100},
	{{255,255,255},{255,255,255},100},
};

ColorPhase color_alg_disco__phasesTilted[] =  {
	{{100,0,0},{255,0,0},1000},
	{{255,0,0},{100,0,0},1000},
};

ColorPhase* color_alg_disco__phases[] = {
	color_alg_disco__phasesUpright,
	color_alg_disco__phasesTilting,
	color_alg_disco__phasesTilted
};

int color_alg_disco__phaseCounts[] = {
	sizeof(color_alg_disco__phasesUpright) / sizeof(ColorPhase),
	sizeof(color_alg_disco__phasesTilting) / sizeof(ColorPhase),
	sizeof(color_alg_disco__phasesTilted) / sizeof(ColorPhase)
};

// ==== public =====

void color_alg_disco__init(DiscoAlgState *state) {
	state->cycleStartTime = currentMillis();
}

bool color_alg_disco__getColor(DiscoAlgState *state, char boxState, unsigned char * result) {
	char stateIndex = boxState-BOX_STATE__UPRIGHT;
	return color_phase__getColor(state->cycleStartTime, color_alg_disco__phases[stateIndex], color_alg_disco__phaseCounts[stateIndex], result);
}

