import time

TSL2571_DEFAULT_ADDRESS = 0x39
TSL2571_GLASS_ATTENUATION_DEFAULT = 0x01

#Command register contants

TSL2571_COMMAND_REGISTER = 0x80
TSL2571_REPEATED_BYTE = 0x00
TSL2571_AUTO_INCREMENT = 0xA0
TSL2571_SPECIAL_NORMAL = 0x00
TSL2571_ALS_INTERRUPT_CLEAR = 0x06

#Enable Register Constants

TSL2571_ENABLE_REGISTER = 0x00
TSL2571_ALS_INTERRUPT_ENABLE = 0x10
TSL2571_WAIT_ENABLE = 0x08
TSL2571_ALS_ENABLE = 0x02
TSL2571_POWER_ON = 0x01

#ALS Integration Timing Register constants

TSL2571_ATIME_REGISTER = 0x01
TSL2571_ATIME_1 = 0xFF        #2.47 ms
TSL2571_ATIME_10 = 0xF6       #27.2 ms
TSL2571_ATIME_37 = 0xDB       #101 ms
TSL2571_ATIME_64 = 0xC0       #174 ms
TSL2571_ATIME_256 = 0x00      #696 ms

#Wait Time Register Constants

TSL2571_WTIME_REGISTER = 0x03
TSL2571_WTIME_1 = 0xFF        #2.72 ms (.032 sec if WLONG)
TSL2571_WTIME_74 = 0xB6       #201 ms (2.4 sec if WLONG)
TSL2571_WTIME_256 = 0x00      #696 ms (8.3 sec if WLONG)

#ALS Interrupt Threshold Registers

TSL2571_LOW_LSB = 0x04
TSL2571_LOW_MSB = 0x05
TSL2571_HIGH_LSB = 0x06
TSL2571_HIGH_LSB = 0x07

#Persistance Register

TSL2571_PERSISTANCE_REGISTER = 0x0C
TSL2571_INTERRUPT_EVERY = 0x00
TSL2571_INTERRUPT_1 = 0x01
TSL2571_INTERRUPT_2 = 0x02
TSL2571_INTERRUPT_3 = 0x03
TSL2571_INTERRUPT_5 = 0x04
TSL2571_INTERRUPT_10 = 0x05
TSL2571_INTERRUPT_15 = 0x06
TSL2571_INTERRUPT_20 = 0x07
TSL2571_INTERRUPT_25 = 0x08
TSL2571_INTERRUPT_30 = 0x09
TSL2571_INTERRUPT_35 = 0x0A
TSL2571_INTERRUPT_40 = 0x0B
TSL2571_INTERRUPT_45 = 0x0C
TSL2571_INTERRUPT_50 = 0x0D
TSL2571_INTERRUPT_55 = 0x0E
TSL2571_INTERRUPT_60 = 0x0F

#Configuration Register

TSL2571_CONFIG_REGISTER = 0x0D
TSL2571_CONFIG_WLONG = 0x02

#Control Register

TSL2571_CONTROL_REGISTER = 0x0F
TSL2571_GAIN_1 = 0x20
TSL2571_GAIN_8 = 0x21
TSL2571_GAIN_16 = 0x22
TSL2571_GAIN_120 = 0x23

#Status Register

TSL2571_STATUS_REGISTER = 0x13
TSL2571_STATUS_ALS_INTERRUPT = 0x10
TSL2571_STATUS_ALS_VALID = 0x01

#ADC Channel Data Registers

TSL2571_DATA_0_LSB = 0x14
TSL2571_DATA_0_MSB = 0x15
TSL2571_DATA_1_LSB = 0x16
TSL2571_DATA_1_MSB = 0x17

class TSL2571():
    def __init__(self, smbus, kwargs):
        self.__dict__.update(kwargs)
        #set address to default if not passed
        if not hasattr(self, 'address'):
            self.address = TSL2571_DEFAULT_ADDRESS
        if not hasattr(self, 'wait_enable'):
            self.wait_enable = TSL2571_WAIT_ENABLE
        if not hasattr(self, 'als_enable'):
            self.als_enable = TSL2571_ALS_ENABLE
        if not hasattr(self, 'power_on'):
            self.power_on = TSL2571_POWER_ON
        if not hasattr(self, 'als_integration_time'):
            self.als_integration_time = TSL2571_ATIME_1
        if not hasattr(self, 'wait_time'):
            self.wait_time = TSL2571_WTIME_1
        if not hasattr(self, 'gain'):
            self.gain = TSL2571_GAIN_1
        if not hasattr(self, 'glass_attenuation'):
            self.glass_attenuation = 1
        self.smbus = smbus

        self.smbus.write_byte_data(self.address, TSL2571_ENABLE_REGISTER | TSL2571_COMMAND_REGISTER, 11);
        time.sleep(.00272)
        self.smbus.write_byte_data(self.address, TSL2571_ATIME_REGISTER | TSL2571_COMMAND_REGISTER, self.als_integration_time);
        self.smbus.write_byte_data(self.address, TSL2571_WTIME_REGISTER | TSL2571_COMMAND_REGISTER, self.wait_time);
        self.smbus.write_byte_data(self.address, TSL2571_CONTROL_REGISTER | TSL2571_COMMAND_REGISTER, self.gain);
        
        
        
    def take_reading(self):
        readings = self.smbus.read_i2c_block_data(self.address, TSL2571_COMMAND_REGISTER | TSL2571_DATA_0_LSB, 4)
        c0 = readings[0] + (readings[1] << 8)
        c1 = readings[2] + (readings[3] << 8)
        counts_per_lux = (self.get_a_time() * self.get_gain()) / (self.glass_attenuation * 53)
        lux1 = (c0 - 2 * c1) / counts_per_lux
        lux2 = (0.6 * c0 - c1) / counts_per_lux
        return max(lux1, lux2, 0)
        
    def get_gain(self):
        gain_index = (self.gain & 0x1f)
        gains = [1,8,16,120]
        return gains[gain_index]
        
    def get_a_time(self):
        return (256-self.als_integration_time) * 2.72
