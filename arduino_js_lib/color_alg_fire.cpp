#include "color_generator.h"

/**
 * The hard-coded duration of the two phases (yello, then yellow-red)
 */
//unsigned long transitionDuration[2] = {4000, 4000};
//unsigned char startColor[2][3] = {{164,164,164},{255,0,255}};
//unsigned char endColor[2][3] = {{255,0,255},{164,164,164}};

typedef struct COLOR_PROGRESS {
	char phaseIndex;
	float phaseProgress;
} ColorProgress;

ColorPhase phases[2] =  {
	{{164,164,164},{255,0,255},4000},
	{{255,0,255},{164,164,164},4000}
};

int phaseCount = sizeof(phases) / sizeof(ColorPhase);

// ==== Private ====

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

void nextPhase(FireAlgState *state) {
	if (state->currentPhase < 1) {
		state->cycleStartTime = currentMillis();
		state->currentPhase++;
	} else {
		color_alg_fire_init(state);
	}
}

void getProgress(ColorPhase *phases, int phaseCount, unsigned long currentDuration, ColorProgress *result) {
	unsigned long skippedDuration = 0;
	for (char i = 0; i<phaseCount; i++) {
		if (currentDuration < skippedDuration + phases[i].duration) {
			result->phaseIndex = i;
			result->phaseProgress  = ((float) (currentDuration - skippedDuration)) / (float) phases[i].duration;
			return;
		}
		skippedDuration += phases[i].duration;
	}
}

unsigned char getColorComponentForProgress(ColorPhase *phases, ColorProgress *progress, char componentIndex) {
	ColorPhase *phase = &phases[progress->phaseIndex];
	int totalColorTransition = ((int) phase->endColor[componentIndex]) - ((int) phase->startColor[componentIndex]);
	unsigned char colorValue = progress->phaseProgress * (float) totalColorTransition + (float) phase->startColor[componentIndex];
	return colorValue;
}

// ==== public =====

void color_alg_fire_init(FireAlgState *state) {
	state->currentPhase = 0;
	state->cycleStartTime = currentMillis();
}

void color_alg_fire_getColor(FireAlgState *state, unsigned char * result) {
	unsigned long currentTime = currentMillis();
	unsigned long currentDuration = getDuration(state->cycleStartTime, currentTime);

	ColorProgress progress = {-1, 0.0};

	getProgress(phases, phaseCount, currentDuration, &progress);
	if (progress.phaseIndex < 0) {
		color_alg_fire_init(state);
		progress.phaseIndex = 0;
		progress.phaseProgress = 0.0;
	}

	result[0] = getColorComponentForProgress(phases, &progress, 0);
	result[1] = getColorComponentForProgress(phases, &progress, 1);
	result[2] = getColorComponentForProgress(phases, &progress, 2);
}

