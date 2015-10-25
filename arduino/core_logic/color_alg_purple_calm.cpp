#include "tilt_light_box.h"

// ==== Private =====

ColorPhase color_alg_purple_calm__phasesUpright[] =  {
//	{{255,0,0},{255,0,0},500}, 
	{{255,0,0},{0,0,255},2000} 
};

ColorPhase color_alg_purple_calm__phasesTilting[] =  {
	{{255,255,0},{255,255,0},100},
	{{255,255,0},{0,127,64},500}
};

ColorPhase color_alg_purple_calm__phasesTilted[] =  {
	{{0,127,64},{0,255,0},1000},
	{{0,255,0},{0,127,0},1000},
};

ColorPhase* color_alg_purple_calm__phases[] = {
	color_alg_purple_calm__phasesUpright,
	color_alg_purple_calm__phasesTilting,
	color_alg_purple_calm__phasesTilted
};

int color_alg_purple_calm__phaseCounts[] = {
	sizeof(color_alg_purple_calm__phasesUpright) / sizeof(ColorPhase),
	sizeof(color_alg_purple_calm__phasesTilting) / sizeof(ColorPhase),
	sizeof(color_alg_purple_calm__phasesTilted) / sizeof(ColorPhase)
};

// ==== public =====

void color_alg_purple_calm__init(PurpleCalmAlgState *state) {
	state->cycleStartTime = currentMillis();
}

bool color_alg_purple_calm__getColor(PurpleCalmAlgState *state, char boxState, unsigned char * result) {
	char stateIndex = boxState-BOX_STATE__UPRIGHT;
	return color_phase__getColor(state->cycleStartTime, color_alg_purple_calm__phases[stateIndex], color_alg_purple_calm__phaseCounts[stateIndex], result);
}

