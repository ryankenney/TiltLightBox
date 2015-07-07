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
var colorAlg = 0;
radio.begin(function () {
    var rx = radio.openPipe('rx', Buffer('e7e7e7e7e7','hex')),
        tx = radio.openPipe('tx', Buffer('c2c2c2c2c2','hex'));
    rx.on('data', function(d) {
        console.log(d);
    });
    radio.printDetails();
    tx.on('ready', function(e){
        console.log("TX Ready");
    });
    rx.on('ready', function(e) {
        console.log("RX Reader");
    });
    tx.on('error', function(e) {
        console.log(e);
    });
    endpoint.on('data', function(d) {
        if(Buffer('0880357f','hex').equals(d)) {
            tx.write(new Buffer([colorAlg]));
            colorAlg = (colorAlg + 1) % 2;
        }
    });
});

console.log(endpoint);
endpoint.startPoll();

