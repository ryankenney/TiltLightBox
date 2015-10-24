var Gpio = require('onoff').Gpio,
  button = new Gpio(12, 'in', 'both');
var debounce = require('debounce');

var lastValue, count=0;

function my_increment(e) {
        count++;
        console.log("Count: "+count);
}
var debounce_increment = debounce(my_increment, 100, true);

button.watch(function(err, value) {
if (lastValue != value && value > 0) {
	debounce_increment();
	//my_increment();	
}
lastValue = value;
});

