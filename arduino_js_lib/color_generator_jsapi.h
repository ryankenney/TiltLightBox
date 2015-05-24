#ifndef COLOR_GENERATOR_JSAPI_INCLUDED
#define COLOR_GENERATOR_JSAPI_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "color_generator.h"

#ifdef __cplusplus
extern "C" {
#endif

NextColorFunction getSingleDirectionColorFunc();

unsigned char * mallocColor();
TiltBox * mallocTiltBox();
int getBoxStartColorRed(TiltBox *box);
int getBoxStartColorBlue(TiltBox *box);
int getBoxStartColorGreen(TiltBox *box);

void setNextColorFunc(TiltBox *box, NextColorFunction func);

void getNextColor(TiltBox *box, unsigned char *result);

int getColorRed(unsigned char *rgb);
int getColorGreen(unsigned char *rgb);
int getColorBlue(unsigned char *rgb);

#ifdef __cplusplus
}
#endif

#endif
