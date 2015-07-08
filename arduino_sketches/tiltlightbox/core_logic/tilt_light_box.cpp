#include "tilt_light_box.h"

// TODO [rkenney]: Remove debug
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// ==== Private =====

typedef struct TILT_LIGHT_BOX_PRIV {
	unsigned long (*millis)();
	int (*random)(int, int);
	void (*sleepMillis)(unsigned long);
	void (*transmitTiltState)(TiltBox *box, unsigned char boxState);
	unsigned char (*receiveThemeChange)(TiltBox *box);
	bool (*tiltSensorIsActive)(TiltBox *box);
	void (*writeVisibleColor)(TiltBox *box, unsigned char r, unsigned char g, unsigned char b);
} TiltLightBoxPriv;

TiltLightBoxPriv tilt_light_box_private;

void tilt_light_box_initColorAlg(TiltBox *box) {
	switch (box->colorAlg) {
	case COLOR_ALG__PURPLE_CALM:
		color_alg_purple_calm__init(&box->purpleCalmAlgState);
		break;
	case COLOR_ALG__DISCO:
		color_alg_disco__init(&box->discoAlgState);
		break;
	}
}

/**
 * Gets the color for the current time from the specific algorithm assigned
 * to the box. Returns false if no color was found because we've exceeded
 * the duration of the color cycle.
 */
bool tilt_light_box_getColorFromAlg(TiltBox *box, unsigned char *result) {
	switch (box->colorAlg) {
	case COLOR_ALG__PURPLE_CALM:
		return color_alg_purple_calm__getColor(&box->purpleCalmAlgState, box->boxState, result);
	case COLOR_ALG__DISCO:
		return color_alg_disco__getColor(&box->discoAlgState, box->boxState, result);
	default:
		return false;
	}
}

void setBoxState(TiltBox *box, unsigned char boxState) {
	box->boxState = boxState;
	tilt_light_box_initColorAlg(box);
}

void setColorAlg(TiltBox *box, int algId) {
	box->colorAlg = algId;
	tilt_light_box_initColorAlg(box);
}

// ==== Public =====

unsigned long currentMillis() {
	return tilt_light_box_private.millis();
}

void setCurrentMillisFunc(unsigned long (*func)()) {
	tilt_light_box_private.millis = func;
}

unsigned long randomValue(int low, int high) {
	return tilt_light_box_private.random(low, high);
}

void setRandomValueFunc(int (*func)(int,int)) {
	tilt_light_box_private.random = func;
}

void setSleepMillisFunc(void (*func)(unsigned long)) {
	tilt_light_box_private.sleepMillis = func;
}

void sleepMillis(unsigned long millis) {
	tilt_light_box_private.sleepMillis(millis);
}

void transmitTiltState(TiltBox *box, unsigned char state) {
	tilt_light_box_private.transmitTiltState(box, state);
}

void setTransmitTiltStateFunc(void (*func)(TiltBox *box, unsigned char boxState)) {
	tilt_light_box_private.transmitTiltState = func;
}

unsigned char receiveThemeChange(TiltBox *box) {
	return tilt_light_box_private.receiveThemeChange(box);
}

void setReceiveThemeChangeFunc(unsigned char (*func)(TiltBox *box)) {
	tilt_light_box_private.receiveThemeChange = func;
}

bool tiltSensorIsActive(TiltBox *box) {
	return tilt_light_box_private.tiltSensorIsActive(box);
}

void setTileSensorIsActiveFunc(bool (*func)(TiltBox *box)) {
	tilt_light_box_private.tiltSensorIsActive = func;
}

void writeVisibleColor(TiltBox *box, unsigned char r, unsigned char g, unsigned char b) {
	tilt_light_box_private.writeVisibleColor(box, r, g, b);
}

void setWriteVisibleColorFunc(void (*func)(TiltBox *box, unsigned char r, unsigned char g, unsigned char b)) {
	tilt_light_box_private.writeVisibleColor = func;
}


TiltBox* createTiltBox() {
	TiltBox* ptr = (TiltBox*) malloc(sizeof(TiltBox));
	setColorAlg(ptr, COLOR_ALG__PURPLE_CALM);
	setBoxState(ptr, BOX_STATE__UPRIGHT);
	return ptr;
}

void getColor(TiltBox *box, unsigned char *result) {
	bool colorFoundWithinCycle = tilt_light_box_getColorFromAlg(box, result);
	if (colorFoundWithinCycle) {
		return;
	}
	// Possibly roll to next state
	if (box->boxState == BOX_STATE__TILTING) {
		setBoxState(box, BOX_STATE__TILTED);
	}
	// Else reset color cycle
	else {
		tilt_light_box_initColorAlg(box);
	}
	// Re-get color
	tilt_light_box_getColorFromAlg(box, result);
}

void runCycle(TiltBox *box) {
	// Read theme request from RF
	unsigned char newTheme = receiveThemeChange(box);

	// Apply any theme request
	if (newTheme != COLOR_ALG__NOOP) {
		setColorAlg(box, newTheme);
	}

	// Read tilt sensor
	bool newlyTilting = false;
	bool isTilted = tiltSensorIsActive(box);
	if (isTilted & !box->wasTilted) {
		newlyTilting = true;
	}

	// Notify master of tilting via RF
	if (newlyTilting) {
		transmitTiltState(box, BOX_STATE__TILTING);
	}

	// Apply any change in tilt state to color algorithm
	if (newlyTilting) {
		setBoxState(box, BOX_STATE__TILTING);
	} else if (isTilted & !box->wasTilted) {
		// Do nothing. The lib rolls the color alg from __TILTING to __TILTED automatically
		// setColorAlg(box, BOX_STATE__TILTED);
	} else if (!isTilted & box->wasTilted) {
		setBoxState(box, BOX_STATE__UPRIGHT);
	}
	box->wasTilted = isTilted;

	// Read next color
	unsigned char color[3] = {0,0,0};
	getColor(box, color);

	// Write new color
	writeVisibleColor(box, color[0], color[1], color[2]);

	// Print debug
	/*
	Serial.print("RGB - ");
	Serial.print(color[0]);
	Serial.print(":");
	Serial.print(color[1]);
	Serial.print(":");
	Serial.print(color[2]);
	Serial.print("\n");
	delay(1000);
	*/
}


#ifdef __cplusplus
}
#endif
