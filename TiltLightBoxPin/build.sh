#!/bin/bash

# Beind error handling to any executable that fails
handle_error() {
        errorCode=$?
        echo "==== FAILURE (exit $errorCode) ===="
        exit $errorCode
}
trap 'handle_error' ERR


pushd core_logic
zip -r ../lib/TiltLightBox.zip *
popd

# ===============
# Compile Options
# ===============
# 
# This option identifies each of the C functions that should be available for direct invocation from Javascript
# -s EXPORTED_FUNCTIONS="['_main',...]" \
# 
# This option's value needs to be large enough to hold each of the Javascript function pointers we pass to the C code
# -s RESERVED_FUNCTION_POINTERS=1
# 
# This option enables more detailed failure messages from Javascript
# -s ASSERTIONS=1
# -s ASSERTIONS=2
# 
# This option defines the compiler optimizations to use
# -O2
# 
# This option keeps the C code available even after the main() method terminates
# -s NO_EXIT_RUNTIME=1
# 
# (not yet tried) This option disables dead code omission. Source: https://github.com/kripken/emscripten/issues/278
# -s LINKABLE=1
# 
# ===============

emcc \
	core_logic/tilt_light_box.cpp \
	core_logic/color_phase.cpp \
	core_logic/color_alg_purple_calm.cpp \
	core_logic/color_alg_disco.cpp \
	core_logic/color_alg_off.cpp \
	core_logic/color_alg_x.cpp \
	js_adaptor/tilt_light_box_jsapi.cpp \
	-o web/tilt_light_box.js \
	-s EXPORTED_FUNCTIONS="['_main','_createTiltBox','_runCycle']" \
	-s RESERVED_FUNCTION_POINTERS=5 \
	-s NO_EXIT_RUNTIME=1 \
	-s ASSERTIONS=2

