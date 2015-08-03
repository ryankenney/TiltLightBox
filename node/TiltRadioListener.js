var Sound = require('node-aplay');
var radio = require('nrf').connect('/dev/spidev0.0',24,25);
radio.channel(0x4c).dataRate('1Mbps').crcBytes(2).autoRetransmit({count:15, delay:4000});
console.log('running');
radio.begin(function () {
    var rx1 = radio.openPipe('rx', Buffer('e7e7e7e7e7','hex')),
        tx1 = radio.openPipe('tx', Buffer('c2c2c2c2c2','hex'));
    rx1.on('data', function(d) {
	new Sound('smb_coin.wav').play();
        console.log(d);
    });
    radio.printDetails();
    tx1.on('ready', function(e){
        console.log("TX Ready");
    });
    rx1.on('ready', function(e) {
        console.log("RX Reader");
    });
    tx1.on('error', function(e) {
        console.log(e);
    });
});
