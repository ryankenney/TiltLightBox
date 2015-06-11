#ifndef COLOR_GENERATOR_INCLUDED
#define COLOR_GENERATOR_INCLUDED

#include <limits.h>
#include "color_phase.h"
#include "color_alg_purple_calm.h"

// TODO [rkenney]: Remove debug
// #include <stdio.h>

#define DELAY_MILLIS 10;
#define COLOR_INCREMENT 4;

#define COLOR_ALG__PURPLE_CALM 1

#define BOX_STATE__UPRIGHT 0
#define BOX_STATE__TILTING 1
#define BOX_STATE__TILTED 2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TILT_BOX {
	unsigned char startColor[3];
	unsigned char endColor[3];
	unsigned long transitionStartTime;
	unsigned long transitionDuration;
	char boxState;
	int colorAlg;
	PurpleCalmAlgState purpleCalmAlgState;
} TiltBox;

/**
 * Returns the color of that box for the current time, given the box's state
 */
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
 * A blocking sleep function. Similar to delay() for arduino.
 */
void sleepMillis(unsigned long millis);

/**
 * Sets the implementation of sleepMillis()
 */
void setSleepMillisFunc(void (*func)(unsigned long));

/**
 * Sets the color algorithm to use for the box
 */
void setColorAlg(TiltBox *box, int algId);

/**
 * Sets the current state of the box. Box state is one of the BOX_STATE__ constants.
 * Note that the box will automatically transition from BOX_STATE__TILTING
 * to BOX_STATE__TILTED when the former animation ends.
 */
void setBoxState(TiltBox *box, char boxState);

#ifdef __cplusplus
}
#endif

#endif