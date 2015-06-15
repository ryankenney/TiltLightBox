#include "tilt_light_box.h"

// TODO [rkenney]: Remove debug
// #include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// ==== Private =====

typedef struct COLOR_GENERATOR_PRIV {
	unsigned long (*millis)();
	int (*random)(int, int);
	void (*sleepMillis)(unsigned long);
} ColorGeneratorPriv;

ColorGeneratorPriv color_generator_private;

void color_generator_initColorAlg(TiltBox *box) {
	switch (box->colorAlg) {
	case COLOR_ALG__PURPLE_CALM:
		color_alg_purple_calm__init(&box->purpleCalmAlgState);
		break;
	}
}

/**
 * Gets the color for the current time from the specific algorithm assigned
 * to the box. Returns false if no color was found because we've exceeded
 * the duration of the color cycle.
 */
bool color_generator_getColorFromAlg(TiltBox *box, unsigned char *result) {
	switch (box->colorAlg) {
	case COLOR_ALG__PURPLE_CALM:
		return color_alg_purple_calm__getColor(&box->purpleCalmAlgState, box->boxState, result);
	default:
		// TODO [rkenney]: Throw an exception?
		return false;
	}
}

// ==== Public =====

unsigned long currentMillis() {
	return color_generator_private.millis();
}

void setCurrentMillisFunc(unsigned long (*func)()) {
	color_generator_private.millis = func;
}

unsigned long randomValue(int low, int high) {
	return color_generator_private.random(low, high);
}

void setRandomValueFunc(int (*func)(int,int)) {
	color_generator_private.random = func;
}

void setSleepMillisFunc(void (*func)(unsigned long)) {
	color_generator_private.sleepMillis = func;
}

void sleepMillis(unsigned long millis) {
	color_generator_private.sleepMillis(millis);
}

TiltBox* createTiltBox() {
	TiltBox* ptr = (TiltBox*) malloc(sizeof(TiltBox));

	// TODO [rkenney]: Remove debug. Defines the color pattern.
	ptr->startColor[0] = 255;
	ptr->startColor[1] = 255;
	ptr->startColor[2] = 0;
	ptr->endColor[0] = 255;
	ptr->endColor[1] = 0;
	ptr->endColor[2] = 0;
	ptr->transitionStartTime = currentMillis();
	ptr->transitionDuration = 2000;
	ptr->boxState = BOX_STATE__UPRIGHT;

	// TODO [rkenney]: Remove debug
	// printf("RGB: %d,%d,%d\n", ptr->startColor[0], ptr->startColor[1], ptr->startColor[2]);

	return ptr;
}

void setColorAlg(TiltBox *box, int algId) {
	box->colorAlg = algId;
	color_generator_initColorAlg(box);
}

void setBoxState(TiltBox *box, char boxState) {
	box->boxState = boxState;
	color_generator_initColorAlg(box);
}

void getColor(TiltBox *box, unsigned char *result) {
	bool colorFoundWithinCycle = color_generator_getColorFromAlg(box, result);
	if (colorFoundWithinCycle) {
		return;
	}
	// Possibly roll to next state
	if (box->boxState == BOX_STATE__TILTING) {
		setBoxState(box, BOX_STATE__TILTED);
	}
	// Else reset color cycle
	else {
		color_generator_initColorAlg(box);
	}
	// Re-get color
	color_generator_getColorFromAlg(box, result);
}


#ifdef __cplusplus
}
#endif
