#include "color_generator_jsapi.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned char* mallocColor() {
	return (unsigned char*) malloc(sizeof(unsigned char));
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

NextColorFunction getSingleDirectionColorFunc() {
	return nextColorInASingleDirection;
}

// Cast to int for Emscripten's (javascript) sake
int getBoxStartColorRed(TiltBox *box) {
	return box->startColor[0];
}
// Cast to int for Emscripten's (javascript) sake
int getBoxStartColorBlue(TiltBox *box) {
	return box->startColor[1];
}
// Cast to int for Emscripten's (javascript) sake
int getBoxStartColorGreen(TiltBox *box) {
	return box->startColor[2];
}

void setNextColorFunc(TiltBox* box, NextColorFunction func) {
	box->nextColorFunction = func;
}

void getNextColor(TiltBox* box, unsigned char *result) {
	box->nextColorFunction(box, result);
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


#ifdef __cplusplus
}
#endif
