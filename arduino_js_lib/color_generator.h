#ifndef COLOR_GENERATOR_INCLUDED
#define COLOR_GENERATOR_INCLUDED

#define DELAY_MILLIS 10;
#define COLOR_INCREMENT 4;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TILT_BOX {
	unsigned char startColor[3];
	unsigned char endColor[3];
	long transitionDuration;
	long totalTransitionCycles;
	long currentCycle;
	void (*nextColorFunction)(struct TILT_BOX *, unsigned char *);
} TiltBox;

typedef void (*NextColorFunction)(TiltBox *box, unsigned char *);

void nextColorInASingleDirection(TiltBox *box, unsigned char *result);

#ifdef __cplusplus
}
#endif

#endif