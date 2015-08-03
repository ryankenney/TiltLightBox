// Basic demo of a sound effect played from a Raspberry Pi via Node.js

var Sound = require('node-aplay');
var play = require('play');
var sleep = require('sleep');
console.log('running');
while (true) {
        console.log("playing sound");
	new Sound('smb_coin.wav').play();
	// Interestingly, if this sleep is here, no matter how long,
	// it causes the program to pause for the entire audio clip
	// to play. Removing it allows the program to run many cycles
	// in parallel with the audio clip. However, it sounds like
	// the total number of parallel clips is exceeded quickly
	// enough that it very nearly sounds like one clip.
	sleep.sleep(1);
}


