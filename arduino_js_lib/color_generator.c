#include <stdlib.h>
#include <stdio.h>

long DELAY_MILLIS = 10;
long COLOR_INCREMENT = 4;

typedef struct TILT_BOX {
	unsigned char startColor[3];
	unsigned char endColor[3];
	long transitionDuration;
	long totalTransitionCycles;
	long currentCycle;
	void (* nextColorFunction)(struct TILT_BOX, unsigned char *);
} TiltBox;

void nextColorInASingleDirection(TiltBox box, unsigned char *result) {
	if (box.currentCycle >= box.totalTransitionCycles) {
		box.currentCycle = 0;
	}
	result[0] = box.startColor[0] + box.currentCycle * (box.endColor[0]-box.startColor[0]) / box.totalTransitionCycles;
	result[1] = box.startColor[1] + box.currentCycle * (box.endColor[1]-box.startColor[1]) / box.totalTransitionCycles;
	result[2] = box.startColor[2] + box.currentCycle * (box.endColor[2]-box.startColor[2]) / box.totalTransitionCycles;
	box.currentCycle++;
}

TiltBox* mallocTiltBox() {
	TiltBox* ptr = (TiltBox*) malloc(sizeof(TiltBox));

	// TODO [rkenney]: Remove debug
	ptr->startColor[0] = 64;
	ptr->startColor[1] = 128;
	ptr->startColor[2] = 255;

	// TODO [rkenney]: Remove debug
	printf("RGB: %d,%d,%d\n", ptr->startColor[0], ptr->startColor[1], ptr->startColor[2]);

	return ptr;
}

// Cast to int for Emscripten's (javascript) sake
int getBoxStartColorRed(TiltBox* box) {
	return box->startColor[0];
}
// Cast to int for Emscripten's (javascript) sake
int getBoxStartColorBlue(TiltBox* box) {
	return box->startColor[1];
}
// Cast to int for Emscripten's (javascript) sake
int getBoxStartColorGreen(TiltBox* box) {
	return box->startColor[2];
}
