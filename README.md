# Ricardo-Stark (Engine Control Unit)

An integrated engine control unit designed to fire and control liquid bi-propellant rocket engines. Stark v1.0 has been tested in several cold flows and hotfire tests for engines ranging from 500N to 5kN. It has been flight tested on Nimbus 24 (ICLR's first liquid rocket launch) at the European Rocketry Challenge '24.

## Hardware (v1.0)
- ESP32-S3 microcontroller
- x2 Servo Channels with voltage monitor
- x1 Pyro Channel with regulated 12V
- x6 24 bit ADC channels
- microSD card logging
- x4 GPIO breakout
- CAN Bus
- USB-C Port

## Software (v1.0)
- Finite State Machine implementation
- Custom ignition sequence with propellant feed delay
- Custom valve angle configuration
- Optional remote configurability to ignition sequence 



