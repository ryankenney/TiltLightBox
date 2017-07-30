var Gpio = require('onoff').Gpio;
var debounce = require('debounce');

class ThemeButtonControl {
    constructor(buttonGpioPin, onPress) {
        this.lastButtonValue = null;
        var debounceButtonClick = debounce(onPress, 100, true);
        var button = new Gpio(buttonGpioPin, 'in', 'both');
        button.watch(function(err, value) {
            if (this.lastButtonValue != value && value > 0) {
                debounceButtonClick();
            }
            this.lastButtonValue = value;
        });
    }
};

module.exports = ThemeButtonControl;
