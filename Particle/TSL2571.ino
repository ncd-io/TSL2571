// This #include statement was automatically added by the Particle IDE.
#include "TSL2571.h"

TSL2571 sensor;

void setup(){
    sensor.init();
    Particle.variable("lux", sensor.lux);
}

int last_checked = 0;
void loop(){
    sensor.loop();
}
