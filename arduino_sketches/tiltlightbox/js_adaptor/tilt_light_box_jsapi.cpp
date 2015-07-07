#include "tilt_light_box_jsapi.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==== Private =====

// TODO [rkenney]: Remove old
//void (*writeColor)(TiltBox *,int,int,int);

int tilt_light_box_jsapi_random(int low, int high) {
	return rand() % (high-low) + low;
}

// NOTE: We wrap the main call with a local function taht
// takes int args. This is necessary because emscripten
// interprets "unsigned chars" as "chars" when casting
// arguments to function pointers.
void (*tilt_light_box_jsapi_writeVisibleColor_AsInts)(TiltBox *, int r, int g, int b);
void tilt_light_box_jsapi_writeVisibleColor(TiltBox * box, unsigned char r, unsigned char g, unsigned char b) {
	tilt_light_box_jsapi_writeVisibleColor_AsInts(box, r, g, b);
}

// ==== Public =====

int main(int argc, char **argv) {

	srand(time(NULL));

	setRandomValueFunc(tilt_light_box_jsapi_random);

	// Main is called more than once. Not always with the function pointers.
	unsigned char i = 1;
	if (argc > 1) {
		int ptr = atoi(argv[i++]);
		setCurrentMillisFunc(reinterpret_cast<unsigned long (*)()>(ptr));
// TODO [rkenney]: Remove old
//		ptr = atoi(argv[i++]);
//		writeColor = reinterpret_cast<void (*)(TiltBox *,int,int,int)>(ptr);
		ptr = atoi(argv[i++]);
		setTransmitTiltStateFunc(reinterpret_cast<void (*)(TiltBox *, unsigned char boxState)>(ptr));
		ptr = atoi(argv[i++]);
		setReceiveThemeChangeFunc(reinterpret_cast<unsigned char (*)(TiltBox *)>(ptr));
		ptr = atoi(argv[i++]);
		setTileSensorIsActiveFunc(reinterpret_cast<bool (*)(TiltBox *)>(ptr));
		ptr = atoi(argv[i++]);
		tilt_light_box_jsapi_writeVisibleColor_AsInts = reinterpret_cast<void (*)(TiltBox *, int, int, int)>(ptr);
		setWriteVisibleColorFunc(tilt_light_box_jsapi_writeVisibleColor);
	}
	return 0;
}

// TODO [rkenney]: Remove old
/*
void tilt_light_box_jsapi_runCycle(TiltBox *box) {

	runCycle(box);

}
*/

#ifdef __cplusplus
}
#endif
