#include "color_generator.h"

// ==== Private ====

typedef struct COLOR_PROGRESS {
	char phaseIndex;
	float phaseProgress;
} ColorProgress;

/**
 * Returns the duration of time between beginning/end times. If end is before the start time,
 * the value is assumed to have rolled over, and is adjusted accordingly (presuming rollover
 * occurs at ULONG_MAX).
 */
unsigned long color_phase__getDuration(unsigned long start, unsigned long end) {
	if (start > end) {
		return ULONG_MAX - start + end;
	} else {
		return end - start;
	}
}

void color_phase__getProgress(ColorPhase *phases, int phaseCount, unsigned long currentDuration, ColorProgress *result) {
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

unsigned char color_phase__getColorComponentForProgress(ColorPhase *phases, ColorProgress *progress, char componentIndex) {
	ColorPhase *phase = &phases[progress->phaseIndex];
	int totalColorTransition = ((int) phase->endColor[componentIndex]) - ((int) phase->startColor[componentIndex]);
	unsigned char colorValue = progress->phaseProgress * (float) totalColorTransition + (float) phase->startColor[componentIndex];
	return colorValue;
}

// ==== public =====

bool color_phase__getColor(unsigned long cycleStartTime, ColorPhase *phases, char phasesCount, unsigned char * result) {

	unsigned long currentTime = currentMillis();
	unsigned long currentDuration = color_phase__getDuration(cycleStartTime, currentTime);

	ColorProgress progress = {-1, 0.0};

	color_phase__getProgress(phases, phasesCount, currentDuration, &progress);
	if (progress.phaseIndex < 0) {
		return false;
	}

	result[0] = color_phase__getColorComponentForProgress(phases, &progress, 0);
	result[1] = color_phase__getColorComponentForProgress(phases, &progress, 1);
	result[2] = color_phase__getColorComponentForProgress(phases, &progress, 2);
	return true;
}

