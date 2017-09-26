#include "TSL2571.h"
#include "Particle.h"

void TSL2571::init(){
    begin();
    
    sendCommand(TSL2571_ENABLE_REGISTER, TSL2571_ALS_ENABLE | TSL2571_POWER_ON | wait_enabled);
    sendCommand(TSL2571_ATIME_REGISTER, 256 - atime);
    sendCommand(TSL2571_WTIME_REGISTER, 256 - wtime);
    sendCommand(TSL2571_CONTROL_REGISTER, gain);
    sendCommand(TSL2571_CONFIG_REGISTER, wlong);
    
    int catime = getAtime();
    
    CPL = (catime * getGain()) / (ga * 53);
    
    loop_delay = getWtime()+catime;
}

void TSL2571::takeReading(){
    int data[4];
    
    readBytes(TSL2571_DATA_0_LSB, data, 4);
    
    int c0 = data[0] + (data[1] << 8);
    int c1 = data[2] + (data[3] << 8);
    
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
    int gains[4] = {1,8,16,120};
    return gains[(gain & 0x1f)];
}

float TSL2571::getAtime(){
    float ttime = atime * 2.72;
    return ttime;
}
float TSL2571::getWtime(){
    float ttime = wtime * 2.72;
    if(wlong == TSL2571_WLONG_ENABLE) ttime *= 12;
    return ttime;
}

void TSL2571::begin(){
    if (!Wire.isEnabled()) {
        Wire.begin();
    }
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
