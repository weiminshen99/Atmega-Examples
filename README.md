
## Program Nano using "arduino" programmer with a USB(serial) cable works!

Config: Mac --> USB(serial) cable --> (USB)Nano

%avrdude -v -v -p atmega328p -c arduino -P /dev/cu.usbserial-1460 -b 57600 -D -U flash:w:nano_blink.hex:i

or with different baudrate 115200

%avrdude -v -v -p atmega328p -c arduino -P /dev/cu.usbserial-1460 -b 115200 -D -U flash:w:nano_blink.hex:i

## Blink the LED on Nano (Atmega328)

Method 1: Mac --> USBasp --> Nano

"make flash" will compile/upload to Nano and LED will blink

Method 2: Arduino-IDE --> USB/serial cable --> Nano

In IDE, open Blink.c, then compile and upload to Nano

## MotorMate (Atmega8)

Custom brushed motor firmware for a cheap 20A ATmega8-based BLDC controller from China

## How to flush atmega-based ESC

https://itsallrc.wordpress.com/2014/04/13/how-to-flash-simonk-firmware/

## Add Position Control to ESP

https://hackaday.com/2016/02/04/adding-position-control-to-an-open-source-brushless-motor-driver/

https://www.youtube.com/watch?v=8CcqD5sw90U

http://vedder.se/2015/01/vesc-open-source-esc/
