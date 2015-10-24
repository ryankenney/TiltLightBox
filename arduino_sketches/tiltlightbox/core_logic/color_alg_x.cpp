#include "tilt_light_box.h"

// ==== Private =====

ColorPhase color_alg_a__phasesUpright[] =  {
	{{0,0,64},{0,0,192},2000},
	{{0,0,255},{0,0,255},50},
	{{0,0,192},{0,0,192},50},
	{{0,0,255},{0,0,255},50},
	{{0,0,192},{0,0,192},50},
	{{0,0,255},{0,0,255},50},
	{{0,0,192},{0,0,64},2000},
};
ColorPhase color_alg_a__phasesTilting[] =  {
	{{0,64,255},{0,64,255},50},
	{{0,64,192},{0,64,192},50},
	{{0,64,255},{0,64,255},50},
	{{0,64,192},{0,64,192},50},
	{{0,64,255},{0,64,255},50},
};
ColorPhase color_alg_a__phasesTilted[] =  {
	{{0,0,192},{0,192,255},2000},
};

ColorPhase color_alg_b__phasesUpright[] =  {
	{{255,0,0},{192,192,0},1000},
	{{255,0,0},{192,192,0},200},
	{{255,0,0},{192,192,0},800},
	{{255,0,0},{192,192,0},1000},
	{{255,0,0},{192,192,0},100},
	{{255,0,0},{192,192,0},100},
};
ColorPhase color_alg_b__phasesTilting[] =  {
	{{0,192,192},{0,192,192},100},
};
ColorPhase color_alg_b__phasesTilted[] =  {
	{{0,0,255},{0,0,255},100},
	{{0,192,192},{0,192,192},100},
};

ColorPhase color_alg_c__phasesUpright[] =  {
	{{0,0,0},{0,0,0},10000},
};
ColorPhase color_alg_c__phasesTilting[] =  {
	{{0,0,0},{0,0,0},100}
};
ColorPhase color_alg_c__phasesTilted[] =  {
	{{0,0,0},{0,0,0},10000},
};

ColorPhase color_alg_d__phasesUpright[] =  {
	{{64,0,0},{0,64,0},2000},
	{{0,128,0},{0,128,0},200},
	{{0,64,0},{0,0,64},2000},
	{{0,0,128},{0,0,128},200},
	{{0,0,64},{64,0,0},2000},
	{{128,0,0},{128,0,0},200},
};
ColorPhase color_alg_d__phasesTilting[] =  {
	{{255,0,0},{255,0,0},200}
};
ColorPhase color_alg_d__phasesTilted[] =  {
	{{32,32,32},{64,16,16},2000},
	{{64,64,64},{64,64,64},200},
};

ColorPhase* color_alg_a__phases[] = {
	color_alg_a__phasesUpright,
	color_alg_a__phasesTilting,
	color_alg_a__phasesTilted
};
ColorPhase* color_alg_b__phases[] = {
	color_alg_b__phasesUpright,
	color_alg_b__phasesTilting,
	color_alg_b__phasesTilted
};
ColorPhase* color_alg_c__phases[] = {
	color_alg_c__phasesUpright,
	color_alg_c__phasesTilting,
	color_alg_c__phasesTilted
};
ColorPhase* color_alg_d__phases[] = {
	color_alg_d__phasesUpright,
	color_alg_d__phasesTilting,
	color_alg_d__phasesTilted
};

int color_alg_a__phaseCounts[] = {
	sizeof(color_alg_a__phasesUpright) / sizeof(ColorPhase),
	sizeof(color_alg_a__phasesTilting) / sizeof(ColorPhase),
	sizeof(color_alg_a__phasesTilted) / sizeof(ColorPhase)
};
int color_alg_b__phaseCounts[] = {
	sizeof(color_alg_b__phasesUpright) / sizeof(ColorPhase),
	sizeof(color_alg_b__phasesTilting) / sizeof(ColorPhase),
	sizeof(color_alg_b__phasesTilted) / sizeof(ColorPhase)
};
int color_alg_c__phaseCounts[] = {
	sizeof(color_alg_c__phasesUpright) / sizeof(ColorPhase),
	sizeof(color_alg_c__phasesTilting) / sizeof(ColorPhase),
	sizeof(color_alg_c__phasesTilted) / sizeof(ColorPhase)
};
int color_alg_d__phaseCounts[] = {
	sizeof(color_alg_d__phasesUpright) / sizeof(ColorPhase),
	sizeof(color_alg_d__phasesTilting) / sizeof(ColorPhase),
	sizeof(color_alg_d__phasesTilted) / sizeof(ColorPhase)
};

// ==== public =====

void color_alg_x__init(XAlgState *state) {
	state->cycleStartTime = currentMillis();
}

bool color_alg_a__getColor(XAlgState *state, char boxState, unsigned char * result) {
	char stateIndex = boxState-BOX_STATE__UPRIGHT;
	return color_phase__getColor(state->cycleStartTime, color_alg_a__phases[stateIndex], color_alg_a__phaseCounts[stateIndex], result);
}
bool color_alg_b__getColor(XAlgState *state, char boxState, unsigned char * result) {
	char stateIndex = boxState-BOX_STATE__UPRIGHT;
	return color_phase__getColor(state->cycleStartTime, color_alg_b__phases[stateIndex], color_alg_b__phaseCounts[stateIndex], result);
}
bool color_alg_c__getColor(XAlgState *state, char boxState, unsigned char * result) {
	char stateIndex = boxState-BOX_STATE__UPRIGHT;
	return color_phase__getColor(state->cycleStartTime, color_alg_c__phases[stateIndex], color_alg_c__phaseCounts[stateIndex], result);
}
bool color_alg_d__getColor(XAlgState *state, char boxState, unsigned char * result) {
	char stateIndex = boxState-BOX_STATE__UPRIGHT;
	return color_phase__getColor(state->cycleStartTime, color_alg_d__phases[stateIndex], color_alg_d__phaseCounts[stateIndex], result);
}

