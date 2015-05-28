#ifndef COLOR_GENERATOR_JSAPI_INCLUDED
#define COLOR_GENERATOR_JSAPI_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <emscripten.h>
#include "color_generator.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Mollocs and initializes a tilt light box object
 */
TiltBox * createTiltBox();

void getNextColor(TiltBox *box, unsigned char *result);

void runCycle(TiltBox *box);

#ifdef __cplusplus
}
#endif

#endif