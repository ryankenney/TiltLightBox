#include "color_generator_jsapi.h"

#ifdef __cplusplus
extern "C" {
#endif

TiltBox* mallocTiltBox() {
	TiltBox* ptr = (TiltBox*) malloc(sizeof(TiltBox));

	// TODO [rkenney]: Remove debug
	ptr->startColor[0] = 255;
	ptr->startColor[1] = 255;
	ptr->startColor[2] = 0;
	ptr->endColor[0] = 255;
	ptr->endColor[1] = 0;
	ptr->endColor[2] = 0;
	ptr->totalTransitionCycles = 100;
	ptr->currentCycle = 0;

	// TODO [rkenney]: Remove debug
	printf("RGB: %d,%d,%d\n", ptr->startColor[0], ptr->startColor[1], ptr->startColor[2]);

	return ptr;
}

// Cast to int for Emscripten's (javascript) sake
int getColorRed(unsigned char *rgb) {
	return rgb[0];
}
// Cast to int for Emscripten's (javascript) sake
int getColorGreen(unsigned char *rgb) {
	return rgb[1];
}
// Cast to int for Emscripten's (javascript) sake
int getColorBlue(unsigned char *rgb) {
	return rgb[2];
}

void (*writeColor)(TiltBox *,int,int,int);

int main(int argc, char **argv) {
	// Main is called more than once. Not always with the function pointer.
	if (argc > 1) {
		int ptr = atoi(argv[1]);
		writeColor = reinterpret_cast<void (*)(TiltBox *,int,int,int)>(ptr);

		// writeColor((TiltBox *) 100, 64, 128, 255);
	}
	return 0;
}

void runCycle(TiltBox *box) {

	unsigned char color[3] = {0,0,0};
	nextColorInASingleDirection(box, color);

	// printf("runCycle calling writeColor(%d,%d,%d,%d)\n", (int) box, color[0], color[1], color[2]);

	writeColor(box, color[0], color[1], color[2]);
}

#ifdef __cplusplus
}
#endif
