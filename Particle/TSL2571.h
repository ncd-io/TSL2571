#include "spark_wiring_i2c.h"
#include "spark_wiring_constants.h"

//Command register contants

#define TSL2571_COMMAND_REGISTER 0x80
#define TSL2571_REPEATED_BYTE 0x00
#define TSL2571_AUTO_INCREMENT 0xA0
#define TSL2571_SPECIAL_NORMAL 0x00
#define TSL2571_ALS_INTERRUPT_CLEAR 0x06

//Enable Register Constants

#define TSL2571_ENABLE_REGISTER 0x00
#define TSL2571_ALS_INTERRUPT_ENABLE 0x10
#define TSL2571_WAIT_ENABLE 0x08
#define TSL2571_ALS_ENABLE 0x02
#define TSL2571_POWER_ON 0x01

//ALS Integration Timing Register constants

#define TSL2571_ATIME_REGISTER 0x01
#define TSL2571_ATIME_1 0xFF        //2.47 ms
#define TSL2571_ATIME_10 0xF6       //27.2 ms
#define TSL2571_ATIME_37 0xDB       //101 ms
#define TSL2571_ATIME_64 0xC0       //174 ms
#define TSL2571_ATIME_256 0x00      //696 ms

//Wait Time Register Constants

#define TSL2571_WTIME_REGISTER 0x03
#define TSL2571_WTIME_1 0xFF        //2.72 ms (.032 sec if WLONG)
#define TSL2571_WTIME_74 0xB6       //201 ms (2.4 sec if WLONG)
#define TSL2571_WTIME_256 0x00      //696 ms (8.3 sec if WLONG)

//ALS Interrupt Threshold Registers

#define TSL2571_LOW_LSB 0x04
#define TSL2571_LOW_MSB 0x05
#define TSL2571_HIGH_LSB 0x06
#define TSL2571_HIGH_LSB 0x07

//Persistance Register

#define TSL2571_PERSISTANCE_REGISTER 0x0C
#define TSL2571_INTERRUPT_EVERY 0x00
#define TSL2571_INTERRUPT_1 0x01
#define TSL2571_INTERRUPT_2 0x02
#define TSL2571_INTERRUPT_3 0x03
#define TSL2571_INTERRUPT_5 0x04
#define TSL2571_INTERRUPT_10 0x05
#define TSL2571_INTERRUPT_15 0x06
#define TSL2571_INTERRUPT_20 0x07
#define TSL2571_INTERRUPT_25 0x08
#define TSL2571_INTERRUPT_30 0x09
#define TSL2571_INTERRUPT_35 0x0A
#define TSL2571_INTERRUPT_40 0x0B
#define TSL2571_INTERRUPT_45 0x0C
#define TSL2571_INTERRUPT_50 0x0D
#define TSL2571_INTERRUPT_55 0x0E
#define TSL2571_INTERRUPT_60 0x0F

//Configuration Register

#define TSL2571_CONFIG_REGISTER 0x0D
#define TSL2571_CONFIG_WLONG 0x02

//Control Register

#define TSL2571_CONTROL_REGISTER 0x0F
#define TSL2571_GAIN_1 0x20
#define TSL2571_GAIN_8 0x21
#define TSL2571_GAIN_16 0x22
#define TSL2571_GAIN_120 0x23

//Status Register

#define TSL2571_STATUS_REGISTER 0x13
#define TSL2571_STATUS_ALS_INTERRUPT 0x10
#define TSL2571_STATUS_ALS_VALID 0x01

//ADC Channel Data Registers

#define TSL2571_DATA_0_LSB 0x14
#define TSL2571_DATA_0_MSB 0x15
#define TSL2571_DATA_1_LSB 0x16
#define TSL2571_DATA_1_MSB 0x17


class TSL2571{
public:
    //I2C Address
    int address = 0x39;
    
    //Glass Attenuation (used for light pipes and glass filters)
    float ga=1;
    int init_options = (TSL2571_WAIT_ENABLE | TSL2571_ALS_ENABLE | TSL2571_POWER_ON);
    int atime = TSL2571_ATIME_1;
    int wtime = TSL2571_WTIME_1;
    int gain = TSL2571_GAIN_1;
    
    int getGain();
    float getAtime();
    
    void sendCommand(int reg, int cmd);
    void readBytes(int reg, int *bytes, int length);
    
    void init();
    void takeReading();
    void loop();
    
    int last_checked=0;
    int loop_delay;
    
    double lux=0;
    
    
};
