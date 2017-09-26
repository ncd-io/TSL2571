import smbus
import time
import tsl2571
# Get I2C bus, this is I2C Bus 1
bus = smbus.SMBus(1)
#kwargs is a Python set that contains the address of your device as well as additional device and calibration values.
#kwargs does not have to be populated as every value is optional and will be replaced with a default value if not is specified.
#kwargs does however need to be instantiated as a set such as below
kwargs = {}

#below is an example of a kwarg declaration that is populated with all of the default values for each user configurable property
#refer to the datasheet for this chip to calculate what values you should be using for your project. For instance if you are using light pipes you would want to alter glass atennuation.
kwargs = {'address': 0x39, 'wait_enable': 0x08, 'als_enable': 0x02, 'power_on': 0x01, 'als_integration_time': 0xFF, 'wait_time': 0xFF, 'gain': 0x20, 'glass_attenuation': 0x01}
#create the TSL2571 object from the TSL2571 library
#the object requires that you pass it the bus object so that it can communicate and share the bus with other chips if necessary
tsl2571 = tsl2571.TSL2571(bus, kwargs)

while True :
    print tsl2571.take_reading()
    #keep in mind the chip can only take readings so many times a second. The actual rate is dependant on your configuration properties.
    #Running a loop in this way for an actual project will result in duplicate data being returned until the chip has taken new readings and set them in the register.
