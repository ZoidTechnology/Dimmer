# Dimmer

A flexible 8-28V 10A PWM dimmer with configurable overcurrent protection.

## Hardware

The dimmer is designed to use separate control and interface PCBs. The interface consists of a rotary encoder and a two digit LED display. The controller uses a STM8S103F3 microcontroller.

## Firmware

The included makefile allows the firmware to be compiled with SDCC on Windows. The makefile can also flash the compiled firmware to the device. This requires a ST-LINK and STVP-STM8 to be installed. The option byte `AFR` must have the `AFR0` bit set. This can be set using STVP.

## Usage

The dimmer can be turned on with a short press of the rotary encoder. The encoder can then be used to increase or decrease the brightness between 0 and 99.

A long press of the encoder will enter the current limit adjustment mode. The encoder can be used to set the limit between 0 and 9.9 amps. Another press of the encoder will apply the changes.

A short press of the encoder will save the brightness and current limit to non-volatile memory and power off the dimmer.

If the current limit is exceeded the output will be disabled and the display will show "O.L." until power is removed.