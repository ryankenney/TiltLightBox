#ifndef COLOR_PHASE_INCLUDED
#define COLOR_PHASE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Color phases define a transition between two colors with a given duration.
 * They are generally strung together (in arrays) to generate patterns.
 */
typedef struct COLOR_PHASE {
	unsigned char startColor[3];
	unsigned char endColor[3];
	unsigned long duration;
} ColorPhase;

/**
 * Gets the RGB value computed by applying the current
 * cycle time to the provided color phase definitions.
 * Returns false if the current cycle time exceeds the
 * duration of all phases.
 */
bool color_phase__getColor(unsigned long cycleStartTime, ColorPhase *phases, char phasesCount, unsigned char * result);

#ifdef __cplusplus
}
#endif

#endif