#include "tilt_light_box_jsapi.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==== Private =====

void (*writeColor)(TiltBox *,int,int,int);

int myRandom(int low, int high) {
	return rand() % (high-low) + low;
}

// ==== Public =====

int main(int argc, char **argv) {

	srand(time(NULL));

	setRandomValueFunc(myRandom);

	// Main is called more than once. Not always with the function pointer.
	if (argc > 1) {
		int ptr = atoi(argv[1]);
		setCurrentMillisFunc(reinterpret_cast<unsigned long (*)()>(ptr));
		ptr = atoi(argv[2]);
		writeColor = reinterpret_cast<void (*)(TiltBox *,int,int,int)>(ptr);
	}
	return 0;
}

void runCycle(TiltBox *box) {

	unsigned char color[3] = {0,0,0};
	getColor(box, color);

	// TODO [rkenney]: Remove debug
	// printf("runCycle calling writeColor(%d,%d,%d,%d)\n", (int) box, color[0], color[1], color[2]);

	writeColor(box, color[0], color[1], color[2]);
}

#ifdef __cplusplus
}
#endif
