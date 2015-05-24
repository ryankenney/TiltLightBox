#!/bin/bash

# Beind error handling to any executable that fails
handle_error() {
        errorCode=$?
        echo "==== FAILURE (exit $errorCode) ===="
        exit $errorCode
}
trap 'handle_error' ERR

#emcc color_generator.c -o color_generator.bc
#emcc color_generator_jsapi.c -o color_generator_jsapi.bc \
#	-s EXPORTED_FUNCTIONS="['_nextColorInASingleDirection','_mallocTiltBox','_getBoxStartColorRed','_getBoxStartColorBlue','_getBoxStartColorGreen']"
#emcc color_generator.bc color_generator_jsapi.bc -o color_generator.js

emcc -O2 color_generator.c color_generator_jsapi.c -o color_generator.js \
	-s EXPORTED_FUNCTIONS="['_nextColorInASingleDirection','_mallocColor','_mallocTiltBox','_getBoxStartColorRed','_getBoxStartColorBlue','_getBoxStartColorGreen','_getSingleDirectionColorFunc','_setNextColorFunc','_getNextColor','_getColorRed','_getColorGreen','_getColorBlue']" \
	-s ASSERTIONS=1

