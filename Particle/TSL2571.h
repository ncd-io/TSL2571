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
#define TSL2571_WAIT_DISABLE 0x08
#define TSL2571_ALS_ENABLE 0x02
#define TSL2571_POWER_ON 0x01

//ALS Integration Timing Register constants

#define TSL2571_ATIME_REGISTER 0x01

//Wait Time Register Constants

#define TSL2571_WTIME_REGISTER 0x03

//Configuration Register

#define TSL2571_CONFIG_REGISTER 0x0D
#define TSL2571_WLONG_ENABLE 0x02
#define TSL2571_WLONG_DISABLE 0x00


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


//These registers are unused in this library, they are only listed for completeness

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


class TSL2571{
public:
    //I2C Address
    int address = 0x39;
    
    //Glass Attenuation (used for light pipes and glass filters)
    float ga=1;
    
    int wait_enabled = TSL2571_WAIT_ENABLE;
    int wtime = 1;
    int wlong = TSL2571_WLONG_DISABLE;
    
    int atime = 1;
    int gain = TSL2571_GAIN_1;
    
    void init();
    void takeReading();
    void loop();
    
    double lux=0;
private:
    double CPL;
    int getGain();
    float getAtime();
    float getWtime();
    int loop_delay;
    int last_checked=0;
    void begin();
    void sendCommand(int reg, int cmd);
    void readBytes(int reg, int *bytes, int length);
};
