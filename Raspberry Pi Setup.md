Setting up Rasberry Pi as TiltLightBox Server
====================

Overview
--------------------

This is what I did to get my Raspberry Pi 2 B running as the control/audio server for the TiltLightBoxes. 


Installed OS
--------------------

I just loaded the Pi with the basic Raspian image.

Enabled SPI and I2C Kernel Modules
--------------------

Launch the Raspberry Pi config tool:

```
sudo raspbi-config
```

Select "Advanced Options"

* Select "SPI"
	* Enable the module on startup
* Select "IC2"
	* Enable the module on startup

(I need to go back verify that IC2 is required. I suspect it is not.)

Reboot the Pi

```
sudo reboot
```

Install libudev and build-essentials
--------------------

```
sudo aptitude install libudev-dev
sudo aptitude install build-essentials
```

Certain node dependencies rely upon the build essentials.

Install nodejs
--------------------

| Source: [Installing node.js on Rasberry Pi](https://learn.adafruit.com/node-embedded-development/installing-node-dot-js) |

Add apt.adafruit.com to your package repository list (/etc/apt/sources.list):

```
curl -sLS https://apt.adafruit.com/add | sudo bash
```

Install Node.js:

```
sudo apt-get install node
```

Verify installation:

```
$ node -v
v0.12.0
```

Download and Install TiltLightBox Application
--------------------

Get the source code:

```
cd /opt/
git clone https://github.com/ryankenney/TiltLightBox.git
cd TiltLightBox
```

Load Node.js dependencies

```
npm install nrf
npm install sleep
npm install readable
npm install usb
```

Configure Application Auto-Start
--------------------

![](fixme.png) Document

Wire-Up Hardware
--------------------

![](fixme.png) Link to wiring for RF and button



