#include "color_generator.h"

// ==== Private =====

ColorPhase phases[2] =  {
	{{164,164,164},{255,0,255},3000},
	{{255,0,255},{164,164,164},3000}
};

int phasesCount = sizeof(phases) / sizeof(ColorPhase);

// ==== public =====

void color_alg_purple_calm__init(PurpleCalmAlgState *state) {
	state->currentPhase = 0;
	state->cycleStartTime = currentMillis();
}

void color_alg_purple_calm__getColor(PurpleCalmAlgState *state, unsigned char * result) {
	bool colorFound = color_phase__getColor(state->cycleStartTime, phases, phasesCount, result);
	if (!colorFound) {
		color_alg_purple_calm__init(state);
		color_phase__getColor(state->cycleStartTime, phases, phasesCount, result);
	}
}

