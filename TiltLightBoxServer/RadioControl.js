var NRF = require('nrf');

class RadioControl {
    constructor(cePin, irqPin, onRadioStart) {

        this.onTiltStateChange = (m) => {};
        let doOnTiltStateChange = (data) => {
            let packet = data.readUInt8(0);
            let state = Math.floor(packet / 100);
            let boxId = packet % 100;
            console.log("RX Read: "+state+","+boxId);
            this.onTiltStateChange(state, boxId);
        };

        var radio = NRF.connect('/dev/spidev0.0', cePin, irqPin);
        radio.channel(0x4c).dataRate('1Mbps').crcBytes(2).autoRetransmit({count:15, delay:4000});

        radio.begin(function () {
            // NOTE: Disabled auto-ack, as this was causing the device
            // buffer to lockup from the acks of the many devices listening
            this.rx1 = radio.openPipe('rx', Buffer('e7e7e7e7e7', 'hex'), {autoAck: false});
            this.tx1 = radio.openPipe('tx', Buffer('c2c2c2c2c2', 'hex'), {autoAck: false});

            // Log on startup
            this.tx1.on('ready', function (e) {
                console.log("TX Ready");
            });
            this.rx1.on('ready', function (e) {
                console.log("RX Reader");
            });

            console.log("=== Radio Enabled ===");
            radio.printDetails();

            // Restart radio on error
            this.tx1.on('error', function (e) {
                console.log(e);
                console.log("Resetting Radio");
                radio.reset();
            });

            // Bind onTilt action
            this.rx1.on('data', doOnTiltStateChange);

            // Notify caller
            if (onRadioStart) { onRadioStart(); }
        });
    }
};

RadioControl.prototype.setOnTiltStateChange = function (callback) {
    this.onTiltStateChange = callback;
};

RadioControl.prototype.sendTheme = function (themeId) {
    console.log("Sending Theme: "+themeIds[index]);
    this.tx1.write(new Buffer(themeId));
};

module.exports = RadioControl;