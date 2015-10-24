var themeIds = [1,2,4,5,7];
var lastThemeIndex = -1;

var Gpio = require('onoff').Gpio,
  button = new Gpio(12, 'in', 'both');
var debounce = require('debounce');

var lastValue, count=0;

function my_increment(e) {
	var index = (lastThemeIndex + 1) % themeIds.length;
	console.log("Theme: "+themeIds[index]);
	lastThemeIndex = index;
}
var debounce_increment = debounce(my_increment, 100, true);

button.watch(function(err, value) {
if (lastValue != value && value > 0) {
	debounce_increment();
	//my_increment();	
}
lastValue = value;
});

