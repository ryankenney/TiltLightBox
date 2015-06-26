#include "tilt_light_box.h"

// ==== Private =====

ColorPhase color_alg_purple_calm__phasesUpright[] =  {
	{{164,164,164},{255,0,255},2000},
	{{255,0,255},{164,164,164},3000},
};

ColorPhase color_alg_purple_calm__phasesTilting[] =  {
	{{0,0,255},{0,0,255},100},
	{{0,255,0},{0,255,0},300},
	{{255,0,0},{255,0,0},100}
};

ColorPhase color_alg_purple_calm__phasesTilted[] =  {
	{{64,164,64},{64,255,64},1000},
	{{64,255,64},{64,164,64},1000},
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
	return color_phase__getColor(state->cycleStartTime, color_alg_purple_calm__phases[boxState], color_alg_purple_calm__phaseCounts[boxState], result);
}

