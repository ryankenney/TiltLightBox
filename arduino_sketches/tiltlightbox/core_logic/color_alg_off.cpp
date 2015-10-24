#include "tilt_light_box.h"

// ==== Private =====

ColorPhase color_alg_off__phasesUpright[] =  {
	{{0,0,0},{0,0,0},10000},
	{{255,0,0},{255,0,0},100},
	{{0,0,0},{0,0,0},10000},
	{{0,0,255},{0,0,255},100},
	{{0,0,0},{0,0,0},10000},
	{{0,255,0},{0,255,0},100}
};

ColorPhase color_alg_off__phasesTilting[] =  {
	{{0,0,0},{0,0,0},100}
};

ColorPhase color_alg_off__phasesTilted[] =  {
	{{0,0,0},{0,0,0},10000},
	{{255,0,0},{255,0,0},100},
	{{0,0,0},{0,0,0},10000},
	{{0,0,255},{0,0,255},100},
	{{0,0,0},{0,0,0},10000},
	{{0,255,0},{0,255,0},100}
};

ColorPhase* color_alg_off__phases[] = {
	color_alg_off__phasesUpright,
	color_alg_off__phasesTilting,
	color_alg_off__phasesTilted
};

int color_alg_off__phaseCounts[] = {
	sizeof(color_alg_off__phasesUpright) / sizeof(ColorPhase),
	sizeof(color_alg_off__phasesTilting) / sizeof(ColorPhase),
	sizeof(color_alg_off__phasesTilted) / sizeof(ColorPhase)
};

// ==== public =====

void color_alg_off__init(OffAlgState *state) {
	state->cycleStartTime = currentMillis();
}

bool color_alg_off__getColor(OffAlgState *state, char boxState, unsigned char * result) {
	char stateIndex = boxState-BOX_STATE__UPRIGHT;
	return color_phase__getColor(state->cycleStartTime, color_alg_off__phases[stateIndex], color_alg_off__phaseCounts[stateIndex], result);
}

