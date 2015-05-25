#ifndef COLOR_GENERATOR_JSAPI_INCLUDED
#define COLOR_GENERATOR_JSAPI_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <emscripten.h>
#include "color_generator.h"

#ifdef __cplusplus
extern "C" {
#endif

NextColorFunction getSingleDirectionColorFunc();

TiltBox * mallocTiltBox();

void getNextColor(TiltBox *box, unsigned char *result);

int getColorRed(unsigned char *rgb);
int getColorGreen(unsigned char *rgb);
int getColorBlue(unsigned char *rgb);

void runCycle(TiltBox *box);

#ifdef __cplusplus
}
#endif

#endif
