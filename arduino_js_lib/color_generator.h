#ifndef COLOR_GENERATOR_INCLUDED
#define COLOR_GENERATOR_INCLUDED

#include <limits.h>
#include "color_alg_fire.h"

// TODO [rkenney]: Remove debug
// #include <stdio.h>

#define DELAY_MILLIS 10;
#define COLOR_INCREMENT 4;

#define COLOR_ALG_FIRE 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TILT_BOX {
	unsigned char startColor[3];
	unsigned char endColor[3];
	unsigned long transitionStartTime;
	unsigned long transitionDuration;
	int colorAlg;
	FireAlgState fireAlgState;
} TiltBox;

void getColor(TiltBox *box, unsigned char *result);

/**
 * An incrementing milliseconds clock time. The rollover value can obtained from ULONG_MAX (limits.h).
 * This is intended to mirror the millis() method provided by Arduino.
 */
unsigned long currentMillis();

/**
 * Sets the implementation of currentMillis()
 */
void setCurrentMillisFunc(unsigned long (*func)());

/**
 * Generates a random number greater than or equal to the provided
 * low value and less than the provided high value.
 */
unsigned long randomValue(int low, int high);

/**
 * Sets the implementation of randomValue()
 */
void setRandomValueFunc(int (*func)(int,int));

/**
 * Sets the color algorithm to use for the box
 */
void setColorAlg(TiltBox *box, int algId);

#ifdef __cplusplus
}
#endif

#endif