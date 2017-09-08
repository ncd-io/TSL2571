#include "TSL2571.h"
#include "Particle.h"

void TSL2571::init(){
    if (!Wire.isEnabled()) {
        Wire.begin();
    }
    loop_delay = wtime+atime;
    sendCommand(TSL2571_ENABLE_REGISTER, init_options);
    sendCommand(TSL2571_ATIME_REGISTER, atime);
    sendCommand(TSL2571_WTIME_REGISTER, wtime);
    sendCommand(TSL2571_CONTROL_REGISTER, gain);
}

void TSL2571::takeReading(){
    
    int data[4];
    
    readBytes(TSL2571_DATA_0_LSB, data, 4);
    
    int c0 = data[0] + (data[1] << 8);
    int c1 = data[2] + (data[3] << 8);
    
    float CPL = (getAtime() * getGain()) / (ga * 53);
    
    float lux1 = (c0 - 2 * c1) / CPL;
    float lux2 = (0.6 * c0 - c1) / CPL;
    
    lux = max(lux1, lux2);
}

void TSL2571::loop(){
    int now=millis();
    if(now-last_checked > loop_delay){
        last_checked=now;
        takeReading();
    }
}

int TSL2571::getGain(){
    int gain_index = (gain & 0x1f);
    int gains[4] = {1,8,16,120};
    return gains[gain_index];
}

float TSL2571::getAtime(){
    return (float)(256-atime) * 2.72;
}

void TSL2571::sendCommand(int reg, int cmd){
    Wire.beginTransmission(address);
    Wire.write(TSL2571_COMMAND_REGISTER | reg);
    Wire.write(cmd);
    Wire.endTransmission();
}

void TSL2571::readBytes(int reg, int *bytes, int length){
    Wire.beginTransmission(address);
    Wire.write(TSL2571_COMMAND_REGISTER | reg);
    Wire.endTransmission();
    Wire.requestFrom(address, length);
    for(int i=0;i<length;i++){
        bytes[i] = Wire.read();
    }
}
