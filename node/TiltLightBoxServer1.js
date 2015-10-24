var Sound = require('node-aplay');
var play = require('play');
var Readable = require('stream').Readable;
var sleep = require('sleep');
var radio = require('nrf').connect('/dev/spidev0.0',24,25);
radio.channel(0x4c).dataRate('1Mbps').crcBytes(2).autoRetransmit({count:15, delay:4000});

console.log('running');

/*
var USB = require('usb');
//var device = USB.findByIds(0x09e8,0x0073);
var device = USB.findByIds(0x045e,0x00cb);
device.open();
console.log(device.interfaces);
var interface = device.interface(0);
interface.claim();
console.log("Kernel active: " + interface.isKernelDriverActive());
//var endpoint = interface.endpoint(0x82);
var endpoint = interface.endpoint(0x07);
*/

var colorAlg = 1;
/*
var keypress = require('keypress');
 
// make `process.stdin` begin emitting "keypress" events 
keypress(process.stdin);
 
// listen for the "keypress" event 
process.stdin.on('keypress', function (ch, key) {
  //console.log('got "keypress"', key);
  if (key && key.ctrl && key.name == 'c') {
	process.exit();
  } else if (key && (key.name == 'right' || key.name == 'left')) {
            colorAlg = ((colorAlg + 2) % 2) + 1;
            tx1.write(new Buffer([colorAlg]));
  }
});
 
process.stdin.setRawMode(true);
process.stdin.resume();
*/

radio.begin(function () {
    var rx1 = radio.openPipe('rx', Buffer('e7e7e7e7e7','hex')),
        tx1 = radio.openPipe('tx', Buffer('c2c2c2c2c2','hex'));
    rx1.on('data', function(d) {
	new Sound('smb_coin.wav').play();
        console.log("RX Read...");
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

var keypress = require('keypress');

// make `process.stdin` begin emitting "keypress" events
keypress(process.stdin);

// listen for the "keypress" event
process.stdin.on('keypress', function (ch, key) {
  //console.log('got "keypress"', key);
  if (key && key.ctrl && key.name == 'c') {
        process.exit();
  } else if (key && (key.name == 'right' || key.name == 'left')) {
            colorAlg = ((colorAlg + 2) % 2) + 1;
            tx1.write(new Buffer([colorAlg]));
  }
});

process.stdin.setRawMode(true);
process.stdin.resume();


});
/*
console.log(endpoint);
endpoint.startPoll();
*/