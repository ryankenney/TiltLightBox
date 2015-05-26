#include "color_generator.h"

/**
 * The hard-coded duration of the two phases (yello, then yellow-red)
 */
unsigned long transitionDuration[2] = {4000, 500};
unsigned char startColor[2][3] = {{255,255,0},{255,255,0}};
unsigned char endColor[2][3] = {{255,255,0},{255,0,0}};;

// ==== Private =====

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

unsigned char getColorComponentForTime(FireAlgState *state, float transitionProgress, int colorComponentIndex) {
	int totalColorTransition = (int) endColor[state->currentPhase][colorComponentIndex] - (int) startColor[state->currentPhase][colorComponentIndex];
	unsigned char colorValue = transitionProgress * (float) totalColorTransition + startColor[state->currentPhase][colorComponentIndex];

	// TODO [rkenney]: Remove debug
	// printf("color: %d - %d = %d -> %d\n", endColor[state->currentPhase][colorComponentIndex], startColor[state->currentPhase][colorComponentIndex], totalColorTransition, colorValue);

	return colorValue;
}

void nextPhase(FireAlgState *state) {
	if (state->currentPhase < 1) {
		state->cycleStartTime = currentMillis();
		state->currentPhase++;
	} else {
		color_alg_fire_init(state);
	}
}

// ==== public =====

void color_alg_fire_init(FireAlgState *state) {
	// Randomly stagger start times
	int halfFisrtDuration = transitionDuration[0]/2;
	state->currentPhase = 0;
	state->cycleStartTime = currentMillis()-randomValue(-halfFisrtDuration, halfFisrtDuration);
}

void color_alg_fire_getColor(FireAlgState *state, unsigned char * result) {
	unsigned long currentTime = currentMillis();
	unsigned long currentDuration = getDuration(state->cycleStartTime, currentTime);
	float transitionProgress;
	if (currentDuration > transitionDuration[state->currentPhase]) {
		nextPhase(state);
	} else {
		transitionProgress = ((float) currentDuration) / ((float) transitionDuration[state->currentPhase]);
	}

	// TODO [rkenney]: Remove debug
	// printf("%lu - %lu = %lu = %f%%\n", currentTime, state->cycleStartTime, currentDuration, transitionProgress*100.0);

	result[0] = getColorComponentForTime(state, transitionProgress, 0);
	result[1] = getColorComponentForTime(state, transitionProgress, 1);
	result[2] = getColorComponentForTime(state, transitionProgress, 2);
}

