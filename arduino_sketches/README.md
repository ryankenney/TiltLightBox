Tilt Switch 5050 Controller
==========

Modules
----------

### arduino_sketches/color_change_demo

A basic demo of color cycling on an Arduino.

### arduino_sketches/tilt-light-box

The central Arduino sketch of this project. It defines an Arduino that:

  - Cycles 5050 LED colors according to a color scheme and tilt state
  - Detects tilt state from an array of tilt sensors
  - Responds to nRF24L01-based requests for theme changes
  - Notifies central control of tilt state changes via nRF24L01

### arduino_sketches/tilt_switch_5050_rf_controller_receiver

This is an example of the simplest nRF24L01 transmitter I got working. Pair this with the "_sender" module.

### arduino_sketches/tilt_switch_5050_rf_controller_sender

This is an example of the simplest nRF24L01 receiver I got working. Pair this with the "_receiver" module.

### arduino_sketches/tilt-light-box_arduino-listener

A basic demo of a receiver of TILT messages from a tilt-light-box, implemented on Arduino. This is just a demo, as TILT messages will be received by a Raspberry Pi, not an Arduino at the end of the day.


Arduino Pins
----------

Here is the most current pinout for the Arduino devices we're using. For historical reasons, not all software modules in this repo necessarily align with this current plan.

Arduino Mini Pro (ATmega328) 3.3v Pin Usage
  - A1: North tilt switch
  - A2: South tilt switch
  - 2: RF Module 8 (IRQ)
  - 3 (PMW): Red LED MOSFET
  - 4:
  - 5 (PMW): Blue LED MOSFET
  - 6 (PMW): Green LED MOSFET
  - 7: East tilt switch
  - 8: West tilt switch
  - 9: RF Module 3 (CE)
  - 10 (SPI SS): RF Module 4 (CSN)
  - 11 (SPI MOSI): RF Module 6 (MOSI)
  - 12 (SPI MISO): RF Module 7 (MISO)
  - 13 (SPI SCK): RF Module 5 (SCK)




