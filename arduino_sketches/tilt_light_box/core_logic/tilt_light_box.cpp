#include "tilt_light_box.h"

// TODO [rkenney]: Remove debug
//#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// ==== Private =====

typedef struct TILT_LIGHT_BOX_PRIV {
	unsigned long (*millis)();
	int (*random)(int, int);
	void (*sleepMillis)(unsigned long);
} TiltLightBoxPriv;

TiltLightBoxPriv tilt_light_box_private;

void tilt_light_box_initColorAlg(TiltBox *box) {
	switch (box->colorAlg) {
	case COLOR_ALG__PURPLE_CALM:
		color_alg_purple_calm__init(&box->purpleCalmAlgState);
		break;
	case COLOR_ALG__DISCO:
		color_alg_disco__init(&box->discoAlgState);
		break;
	}
}

/**
 * Gets the color for the current time from the specific algorithm assigned
 * to the box. Returns false if no color was found because we've exceeded
 * the duration of the color cycle.
 */
bool tilt_light_box_getColorFromAlg(TiltBox *box, unsigned char *result) {
	switch (box->colorAlg) {
	case COLOR_ALG__PURPLE_CALM:
		return color_alg_purple_calm__getColor(&box->purpleCalmAlgState, box->boxState, result);
	case COLOR_ALG__DISCO:
		return color_alg_disco__getColor(&box->discoAlgState, box->boxState, result);
	default:
		// TODO [rkenney]: Throw an exception?
		return false;
	}
}

// ==== Public =====

unsigned long currentMillis() {
	return tilt_light_box_private.millis();
}

void setCurrentMillisFunc(unsigned long (*func)()) {
	tilt_light_box_private.millis = func;
}

unsigned long randomValue(int low, int high) {
	return tilt_light_box_private.random(low, high);
}

void setRandomValueFunc(int (*func)(int,int)) {
	tilt_light_box_private.random = func;
}

void setSleepMillisFunc(void (*func)(unsigned long)) {
	tilt_light_box_private.sleepMillis = func;
}

void sleepMillis(unsigned long millis) {
	tilt_light_box_private.sleepMillis(millis);
}

TiltBox* createTiltBox() {
	TiltBox* ptr = (TiltBox*) malloc(sizeof(TiltBox));
	setColorAlg(ptr, COLOR_ALG__PURPLE_CALM);
	setBoxState(ptr, BOX_STATE__UPRIGHT);
	return ptr;
}

void setColorAlg(TiltBox *box, int algId) {
	box->colorAlg = algId;
	tilt_light_box_initColorAlg(box);
}

void setBoxState(TiltBox *box, char boxState) {
	box->boxState = boxState;
	tilt_light_box_initColorAlg(box);
}

void getColor(TiltBox *box, unsigned char *result) {
	bool colorFoundWithinCycle = tilt_light_box_getColorFromAlg(box, result);
	if (colorFoundWithinCycle) {
		return;
	}
	// Possibly roll to next state
	if (box->boxState == BOX_STATE__TILTING) {
		setBoxState(box, BOX_STATE__TILTED);
	}
	// Else reset color cycle
	else {
		tilt_light_box_initColorAlg(box);
	}
	// Re-get color
	tilt_light_box_getColorFromAlg(box, result);
}


#ifdef __cplusplus
}
#endif
