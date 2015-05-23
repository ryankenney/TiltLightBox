emcc color_generator.c -o color_generator.js -s EXPORTED_FUNCTIONS="['_nextColorInASingleDirection','_mallocTiltBox','_getBoxStartColorRed','_getBoxStartColorBlue','_getBoxStartColorGreen']"

#emcc color_generator.c -o dummy.html -s EXPORTED_FUNCTIONS="['_nextColorInASingleDirection','_mallocTiltBox','_getBoxStartColorRed','_getBoxStartColorBlue','_getBoxStartColorGreen']"
