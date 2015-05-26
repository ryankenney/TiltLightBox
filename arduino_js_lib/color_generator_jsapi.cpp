#include "color_generator_jsapi.h"

#ifdef __cplusplus
extern "C" {
#endif

TiltBox* mallocTiltBox() {
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

	// TODO [rkenney]: Remove debug
	// printf("RGB: %d,%d,%d\n", ptr->startColor[0], ptr->startColor[1], ptr->startColor[2]);

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
		setCurrentMillisFunc(reinterpret_cast<unsigned long (*)()>(ptr));
		ptr = atoi(argv[2]);
		writeColor = reinterpret_cast<void (*)(TiltBox *,int,int,int)>(ptr);
	}
	return 0;
}

void runCycle(TiltBox *box) {

	unsigned char color[3] = {0,0,0};
	nextColorInASingleDirection(box, color);

	// TODO [rkenney]: Remove debug
	// printf("runCycle calling writeColor(%d,%d,%d,%d)\n", (int) box, color[0], color[1], color[2]);

	writeColor(box, color[0], color[1], color[2]);
}

#ifdef __cplusplus
}
#endif
