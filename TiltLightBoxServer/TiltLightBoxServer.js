var Sound = require('node-aplay');
var RadioControl = require('./RadioControl.js');
var KeyboardControl = require('./KeyboardControl.js');
var ThemeButtonControl = require('./ThemeButtonControl.js');
var BowlingScore = require('./BowlingScore.js');

/* == Radio Pins ==
 * VCC: Red
 * CSN: Orange
 * MOSI: Blue
 * IRQ: Green
 * GND: Grey
 * CE: Yellow
 * SCK: Purple
 * MISO: Brown
 *
 * == Raspberry Pi Pins ==
 * Pin 01 / 3.3V: Red
 * Pin 14 / GND: Grey
 * Pin 18 / GPIO 24: Yellow
 * Pin 19 / GPIO 10 /  SPI_MOSI: Blue
 * Pin 21 / GPIO 09 /  SPI_MISO: Brown
 * Pin 22 / GPIO 25: Green
 * Pin 23 / GPIO 11 /  SPI_CLK: Purple
 * Pin 24 / GPIO 08 /  SPI_CE0: Orange
 */

let themeIds = [1,2,4,5,7];
let lastThemeIndex = -1;

console.log('App Starting...');

let radio = null;
let score = new BowlingScore();

function sendNextTheme() {
    var index = (lastThemeIndex + 1) % themeIds.length;
    radio.sendTheme(themeIds[index]);
    lastThemeIndex = index;
}

// Initialize radio communication with boxes/pins
new Promise((resolve) => {
    radio = new RadioControl(24, 25, resolve)
    resolve();
}).
// Bind sound effects to "tilt" action from boxes/pins
then(() => {
    radio.setOnTilt((state, boxId) => {
        switch (state) {
            case 1:
                new Sound('/bm/TiltLightBox/node/smb_coin.wav').play();
                score.pinStateChanged(boxId, true)
                break;
            case 2:
                score.pinStateChanged(boxId, false)
                break;
            default:
                break;
        }
    });
}).
// Bind local keyboard control (for testing)
then(() => {
    new KeyboardControl(sendNextTheme);
}).
// Bind theme-change GPIO button
then(() => {
    new ThemeButtonControl(12, sendNextTheme);
}).
catch((err) => {
    console.log("Unexpected Error");
    console.error(err);
});




