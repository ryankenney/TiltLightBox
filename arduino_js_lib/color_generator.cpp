#include "color_generator.h"

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

void initColorAlg(TiltBox *box) {
	switch (box->colorAlg) {
	case COLOR_ALG__PURPLE_CALM:
		color_alg_purple_calm__init(&box->purpleCalmAlgState);
		break;
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

void setColorAlg(TiltBox *box, int algId) {
	box->colorAlg = algId;
	initColorAlg(box);
}

void setBoxState(TiltBox *box, char boxState) {
	box->boxState = boxState;
	initColorAlg(box);
}

void getColor(TiltBox *box, unsigned char *result) {
	switch (box->colorAlg) {
	case COLOR_ALG__PURPLE_CALM:
		color_alg_purple_calm__getColor(&box->purpleCalmAlgState, box->boxState, result);
		break;
	}
}

#ifdef __cplusplus
}
#endif
