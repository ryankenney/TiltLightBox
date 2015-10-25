Wiring Diagrams
================

Raspberry Pi Pinout
----------------

The wiring of Raspberry Pi devices can get confusing for a couple of reason.
First, they come in multiple versions. Be sure you have the right pinout diagram for you model.
Second, they have two numbering systems on each device: numbered pins and GPIO pins.
My understanding is that GPIO pins correspond to the chip pins, while the numbered pins are a Pi-specific construct.
The frustrating thing is that the plethora of libraries and sample code out there
doesn't often identify which combination of models/numbering systems they are using.

In any case, here is the pinout diagram for the model I'm using (Raspberry PI 2 B v1.1):

[![alt text][2]][1]

  [1]: raspberry-pi-2b-pins_thumb.png
  [2]: raspberry-pi-2b-pins_thumb.png (Wiring Diagram)

Raspberry PI RF Wiring
----------------

Here is the wiring table for a Raspberry PI 2B to a nRF24L01 RF adapter:

| Pi #    | Pi GPIO  | RF Pin  | My Cable |
| ------- | -------  | ------- | -------- |
| 1       | 3.3v     | VCC     | Red      |
| 14      | Ground   | GND     | Grey     |
| 18      | GPIO 24  | CE      | Yellow   |
| 19      | GPIO 01  | MOSI    | Blue     |
| 21      | GPIO 09  | MISO    | Brown    |
| 22      | GPIO 25  | IRQ     | Green    |
| 23      | GPIO 11  | SCK     | Purple   |
| 24      | GPIO 08  | CSN     | Orange   |


Raspberry PI Button Wiring
----------------

![](fixme.png) Document

