#ifndef COLOR_GENERATOR_INCLUDED
#define COLOR_GENERATOR_INCLUDED

#include <limits.h>
#include "color_alg_fire.h"

#define DELAY_MILLIS 10;
#define COLOR_INCREMENT 4;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TILT_BOX {
	unsigned char startColor[3];
	unsigned char endColor[3];
	unsigned long transitionStartTime;
	unsigned long transitionDuration;
	// TODO [rkenney]: Make this clock-based instead of cycle based (more consistent)
	void (*nextColorFunction)(struct TILT_BOX *, unsigned char *);
	int colorAlg;
	FireAlgState fireAlgState;
} TiltBox;

typedef void (*NextColorFunction)(TiltBox *box, unsigned char *);

void nextColorInASingleDirection(TiltBox *box, unsigned char *result);

/**
 * An incrementing milliseconds clock time. The rollover value can obtained from ULONG_MAX (limits.h).
 * This is intended to mirror the millis() method provided by Arduino.
 */
unsigned long currentMillis();

/**
 * Sets the implementation of currentMillis()
 */
void setCurrentMillisFunc(unsigned long (*func)());

#ifdef __cplusplus
}
#endif

#endif