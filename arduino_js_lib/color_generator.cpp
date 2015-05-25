#include "color_generator.h"

#ifdef __cplusplus
extern "C" {
#endif

void nextColorInASingleDirection(TiltBox *box, unsigned char *result) {
	if (box->currentCycle >= box->totalTransitionCycles) {
		box->currentCycle = 0;
	}
	result[0] = box->startColor[0] + box->currentCycle * (box->endColor[0]-box->startColor[0]) / box->totalTransitionCycles;
	result[1] = box->startColor[1] + box->currentCycle * (box->endColor[1]-box->startColor[1]) / box->totalTransitionCycles;
	result[2] = box->startColor[2] + box->currentCycle * (box->endColor[2]-box->startColor[2]) / box->totalTransitionCycles;
	box->currentCycle++;
}

#ifdef __cplusplus
}
#endif
