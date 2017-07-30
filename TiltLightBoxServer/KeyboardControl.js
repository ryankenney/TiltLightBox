var keypress = require('keypress');

class KeyboardControl {
    constructor(themeChangeAction) {
        console.log("Keyboard Input Enabled");
        console.log("  c:          Exit program");
        console.log("  arrow-left: Change theme");

        // Make process.stdin begin emitting "keypress" events
        keypress(process.stdin);

        // Bind listener to key presses
        process.stdin.on('keypress', function (ch, key) {
            // c: Exit program
            if (key && key.ctrl && key.name == 'c') {
                process.exit();
            }
            // arrow-left: Change theme
            else if (key && (key.name == 'left')) {
                themeChangeAction();
            }
        });

        // Resume reading stdin
        process.stdin.resume();
    }
};

module.exports = KeyboardControl;
