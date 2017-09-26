# Usage

This library provides a class for reading lux from the TSL2571. The tsl2571.ino file provides a simple use case for the Particle cloud.

>Create a new instance of the sensor
```cpp
TSL2571 Sensor;
```
>Enable/Disable the Wait Time, the delay between read cycles (defaults to TSL2571_WAIT_ENABLE)
>>init() must be called after this is set
```cpp
Sensor.wait_enable = TSL2571_WAIT_DISABLE;
```

>Set the Wait Time, expects a value between 1-255 which represents 2.47 increments (defaults to 1: 2.72 ms), this time is different if the WLONG flag is set
>>init() must be called after this is set
```cpp
//201 ms
Sensor.wtime = 74;
```

>Set the ADC Integration time, expects a value between 1-255 which represents 2.47 increments(defaults to 1: 2.47 ms)
>>init() must be called after this is set
```cpp
//27.2 ms
Sensor.atime = 10;
```

>Set the gain (defaults to TSL2571_GAIN_1)
>>init() must be called after this is set
```cpp
Sensor.gain = TSL2571_GAIN_8;
```

>Set the WLONG flag, this increases the wait time by a factor of 12 (Defaults to TSL2571_WLONG_DISABLE)
>>init() must be called after this is set
```cpp
Sensor.wlong = TSL2571_WLONG_ENABLE;
```

>Initialize the sensor
```cpp
Sensor.init();
```

>Take readings from the sensor (unless you are taking one-shot readings, it is better to use the "loop" method, which ensures the correct amount of time has passed since the last reading)
```cpp
Sensor.takeReading();
```

>Take readings at the appropriate interval
``cpp
Sensor.loop();
```

>Get the current value
```cpp
double lux = Sensor.lux;
```
