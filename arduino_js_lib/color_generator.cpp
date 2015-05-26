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
} ColorGeneratorPriv;

ColorGeneratorPriv color_generator_private;

/**
 * Returns the duration of time between beginning/end times. If end is before the start time,
 * the value is assumed to have rolled over, and is adjusted accordingly (presuming rollover
 * occurs at ULONG_MAX).
 */
unsigned long getDuration(unsigned long start, unsigned long end) {
	if (start > end) {
		return ULONG_MAX - start + end;
	} else {
		return end - start;
	}
}

unsigned char getColorComponentForTime(TiltBox *box, float transitionProgress, int colorComponentIndex) {
	int totalColorTransition = (int) box->endColor[colorComponentIndex] - (int) box->startColor[colorComponentIndex];
	unsigned char colorValue = transitionProgress * (float) totalColorTransition + box->startColor[colorComponentIndex];

	// TODO [rkenney]: Remove debug
	// printf("color: %d - %d = %d -> %d\n", box->endColor[colorComponentIndex], box->startColor[colorComponentIndex], totalColorTransition, colorValue);

	return colorValue;
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

void setColorAlg(TiltBox *box, int algId) {
	switch (algId) {
	case COLOR_ALG_FIRE:
		box->colorAlg = COLOR_ALG_FIRE;
		color_alg_fire_init(&box->fireAlgState);
		break;
	}
}

void getColor(TiltBox *box, unsigned char *result) {
	switch (box->colorAlg) {
	case COLOR_ALG_FIRE:
		color_alg_fire_getColor(&box->fireAlgState, result);
		break;
	}
}

#ifdef __cplusplus
}
#endif
