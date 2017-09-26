# About

This Library is intended for use with any TSL2571 board available from ncd.io

## Developer information
NCD has been designing and manufacturing computer control products since 1995.  We have specialized in hardware design and manufacturing of Relay controllers for 20 years.  We pride ourselves as being the industry leader of computer control relay products.  Our products are proven reliable and we are very excited to support Particle.  For more information on NCD please visit ncd.io

## Requirements
- The Python SMBus Module: https://pypi.python.org/pypi/smbus-cffi/
- An I2C connection to a TSL2571 Chip
- Knowledge base for developing and programming with Python.

## Version
1.0.0

## How to use this library

>The libary must be imported into your application. Once it is imported you can create a TSL2571 object and start to
>communicate to the chip. You can optionally pass in a kwarg to the object at instantiation that will override the default
>configuration options.

### Public accessible methods
```cpp
take_reading()
```
>This function communicates to the chip and gets the lux readings back based on the light levels and configuration
>properties passed to the TSL2571 object at instantiation
