var Sound = require('node-aplay');
var play = require('play');
var Readable = require('stream').Readable;
var sleep = require('sleep');
var radio = require('nrf').connect('/dev/spidev0.0',24,25);
radio.channel(0x4c).dataRate('1Mbps').crcBytes(2).autoRetransmit({count:15, delay:4000});

console.log('running');
var USB = require('usb');
var device = USB.findByIds(0x09e8,0x0073);
device.open();
var interface = device.interface(1);
interface.claim();
console.log("Kernel active: " + interface.isKernelDriverActive());
var endpoint = interface.endpoint(0x82);
var colorAlg = 1;
radio.begin(function () {
    var rx1 = radio.openPipe('rx', Buffer('e7e7e7e7e7','hex')),
        tx1 = radio.openPipe('tx', Buffer('c2c2c2c2c2','hex'));
//	rx2 = radio.openPipe('rx', Buffer('0909090909','hex')),
//	tx2 = radio.openPipe('tx', Buffer('2929292929','hex'));
    rx1.on('data', function(d) {
	new Sound('force2pcm.wav').play();
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
    endpoint.on('data', function(d) {
	console.log(d);
        if(Buffer('0880357f','hex').equals(d)) {
            colorAlg = ((colorAlg + 2) % 2) + 1;
            tx1.write(new Buffer([colorAlg]));
        } else if(Buffer('0880367f','hex').equals(d)) {
            colorAlg = ((colorAlg + 2) % 2) + 1;
            tx1.write(new Buffer([colorAlg]));
	}
    });
});

console.log(endpoint);
endpoint.startPoll();

