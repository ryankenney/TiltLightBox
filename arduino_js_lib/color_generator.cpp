#include "color_generator.h"

// TODO [rkenney]: Remove debug
// #include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// ==== Private =====

unsigned long (*millis)();

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

#define COLOR_ALG_FIRE 1

unsigned long currentMillis() {
	return millis();
}

void setCurrentMillisFunc(unsigned long (*func)()) {
	millis = func;
}

void setAlg(TiltBox *box, int algId) {
	switch (algId) {
	case COLOR_ALG_FIRE:
		box->colorAlg = COLOR_ALG_FIRE;
		color_alg_fire_init(&box->fireAlgState);
		break;
	}
}

void nextColorInASingleDirection(TiltBox *box, unsigned char *result) {
	unsigned long currentTime = currentMillis();
	unsigned long currentDuration = getDuration(box->transitionStartTime, currentTime);
	float transitionProgress;
	if (currentDuration > box->transitionDuration) {
		box->transitionStartTime = currentTime;
		transitionProgress = 0.0;
	} else {
		transitionProgress = ((float) currentDuration) / ((float) box->transitionDuration);
	}

	// TODO [rkenney]: Remove debug
	// printf("%lu - %lu = %lu = %f%%\n", currentTime, box->transitionStartTime, currentDuration, transitionProgress*100.0);

	result[0] = getColorComponentForTime(box, transitionProgress, 0);
	result[1] = getColorComponentForTime(box, transitionProgress, 1);
	result[2] = getColorComponentForTime(box, transitionProgress, 2);
}

#ifdef __cplusplus
}
#endif
