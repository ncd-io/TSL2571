// This #include statement was automatically added by the Particle IDE.
#include "TSL2571.h"

TSL2571 sensor;

void setup(){
    sensor.init();
    Particle.variable("lux", sensor.lux);
}

void loop(){
    sensor.loop();
}
