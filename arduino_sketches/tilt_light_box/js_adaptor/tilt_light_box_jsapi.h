#ifndef COLOR_GENERATOR_JSAPI_INCLUDED
#define COLOR_GENERATOR_JSAPI_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <emscripten.h>
#include "../core_logic/tilt_light_box.h"

#ifdef __cplusplus
extern "C" {
#endif

void getNextColor(TiltBox *box, unsigned char *result);

void runCycle(TiltBox *box);

#ifdef __cplusplus
}
#endif

#endif
