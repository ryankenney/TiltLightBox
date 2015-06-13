#include "tilt_light_box.h"

// ==== Private =====

ColorPhase phasesUpright[] =  {
	{{164,164,164},{255,0,255},2000},
	{{255,0,255},{164,164,164},3000},
};

ColorPhase phasesTilting[] =  {
	{{0,0,255},{0,0,255},100},
	{{0,255,0},{0,255,0},300},
	{{255,0,0},{255,0,0},100}
};

ColorPhase phasesTilted[] =  {
	{{64,164,64},{64,255,64},1000},
	{{64,255,64},{64,164,64},1000},
};

// TODO [rkenney]: Figure out how to make this work
// ColorPhase phases[3]* = {
// 	phasesStanding,
// 	phasesTilting,
// 	phasesTilted
// };

int phaseCounts[] = {
	sizeof(phasesUpright) / sizeof(ColorPhase),
	sizeof(phasesTilting) / sizeof(ColorPhase),
	sizeof(phasesTilted) / sizeof(ColorPhase)
};

// ==== public =====

void color_alg_purple_calm__init(PurpleCalmAlgState *state) {
	state->cycleStartTime = currentMillis();
}

bool color_alg_purple_calm__getColor(PurpleCalmAlgState *state, char boxState, unsigned char * result) {

	// TODO [rkenney]: Replace this with the array definition commented out above
	ColorPhase *phase;
	switch (boxState) {
	case BOX_STATE__UPRIGHT:
		phase = phasesUpright;
		break;
	case BOX_STATE__TILTING:
		phase = phasesTilting;
		break;
	case BOX_STATE__TILTED:
		phase = phasesTilted;
		break;
	}

	return color_phase__getColor(state->cycleStartTime, phase, phaseCounts[boxState], result);
}

