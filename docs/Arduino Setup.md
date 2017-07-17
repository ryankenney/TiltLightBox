Arduino Setup for TiltLightBox
====================

Overview
--------------------

This is what I did to get load the TiltLightBox software on to my Arduino Mini Pro 3.3v devices.

Loaded Dependencies into Arduino IDE
--------------------

I forked an tagged the specific versions of the libraries we depend upon in order to ensure compatiblity, so all you need to do is clone my forks. The easiest way to get the libraries into the Arduino IDE is to git clone the repos right into your Arduino IDE libraries directory (~/sketchbook/libraries/ on linux).

It's entirely likely that the lastest versions of the modules in the upstream repos will work just fine, but here's how you get the exact versions I was using into Arduino IDE:

```
cd ~/sketchbook/libraries/
git clone -b TiltLightBox_v1.0 https://github.com/ryankenney/SPI.git 
git clone -b TiltLightBox_v1.0 https://github.com/ryankenney/RF24.git
git clone -b TiltLightBox_v1.0 https://github.com/ryankenney/FastLED.git
```

Loaded TiltLightBox into Arduino IDE
--------------------

If you havene't already, clone our repo:

```
git clone https://github.com/ryankenney/TiltLightBox.git
```

Let's call the root of that repo ```$TLB_HOME```.

You need to load the "arduino/core_logic/" directory into your Arduino IDE libraries. In linux, this is most easly accomlished with a symlink:

```
ln -s $TLB_HOME/arduino/core_logic ~/sketchbook/libraries/TiltLightBox
```

Loaded Arduino Sketch onto Arduino
--------------------

At this point, you can simply deploy this .ino file to an Arduino Mini Pro using your Arduino IDE:

```
$TLB_HOME/arduino/core_logic/tiltlightbox.ino
```


