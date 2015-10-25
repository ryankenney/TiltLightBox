Setting up Rasberry Pi as TiltLightBox Server
====================

Overview
--------------------

This is what I did to get my Raspberry Pi 2 B running as the control/audio server for the TiltLightBoxes. 


Installed OS
--------------------

I just loaded the Pi with the basic NOOBS Raspian image.

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

Installed nodejs
--------------------

> Source: [Installing node.js on Rasberry Pi](https://learn.adafruit.com/node-embedded-development/installing-node-dot-js)

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

Downloaded/Installed TiltLightBox Application
--------------------

Get the source code:

```
cd /opt/
git clone https://github.com/ryankenney/TiltLightBox.git
```

Load Node.js dependencies

```
cd /opt/TiltLightBox/node
npm install nrf
npm install sleep
npm install readable
npm install usb
```

Configured Application Auto-Start
--------------------

![](fixme.png) Verify that this section is accurate. Written from memory.

Install forever module (monitors a Node.js process and restarts it if it dies):

```
cd /opt/TiltLightBox/node
sudo -i npm install forever -g
```

Install crontask to launch forever monitor on startup:

```
sudo crontab -u root -e
```

... adding line:

```
@reboot /usr/bin/sudo -u root -H /usr/local/bin/forever start /opt/TiltLightBox/node/TiltLightBoxServer.js >> /var/log/tiltlightbox.log 2>&1
```

Wired-Up Hardware
--------------------

See [Wiring Diagrams](Wiring Diagrams.md) for instructions on wiring up the following hardware to the Raspberry Pi:

* nRF24L01 radio antenna (for communciation with light boxes)
* push button (for change of color/sound themes)

Starting, Stopping, and Monitoring the Server
--------------------

You can see the processes that the forever module is monitoring with this (you should see TiltLightBox listed):

```
sudo forever list
```

If you kill the TiltLightBox process with ps, forever will just restart it, so here's how you properly stop the TiltLightBox process:

```
sudo forever stopall
```

(...or you could use ps to kill the forever process, then the TiltLightBox process.)

Once you kill TiltLightBox you can manually start the process in the forground with:

```
cd /opt/TiltLightBox/node
sudo node TiltLightBoxServer.js
```

If you want to launch the TiltLightBox in the background again (managed by forever), it's easiest to simply reboot.

You can see the output of forever-managed TiltLightBox process here: 

```
/var/log/tiltlightbox.log
```

