// Library for a Capacitive Soil Moisture Sensor
// Written by Ben Dodd (mitgobla)

#ifndef MBED_MOISTURE_SENSOR_H
#define MBED_MOISTURE_SENSOR_H

#include "mbed.h"


class MoistureSensor {
public:
    /** Create a MoistureSensor object connected to an analog input pin.
    *
    * @param analogIn pin connected to analog out pin on sensor
    */
    MoistureSensor(PinName analogIn);

    /** Read the raw output from the Moisture sensor
    @return float value of raw reading.
    */
    float getRawReading();

    /** Read the clamped output from the Moisture sensor, between the
    dry reading and wet reading, mapped to between 0 and 1.

    @return float value of clamped reading.
    */
    float getClampedReading();

    /** Set the dry (high) value in which the clamped reading
    will be set to if the raw reading is above this value.
    */
    virtual void setDryValue();

    /** Set the wet (low) value in which the clamped reading
    will be set to if the raw reading is below this value.
    */
    virtual void setWetValue();

    /** Get the dry (high) value in which the clamped reading
    will be set to if the raw reading is above this value.

    @return float value of the dry (high) reading
    */
    float getDryValue();

    /** Get the wet (low) value in which the clamped reading
    will be set to if the raw reading is below this value.

    @return float value of the wet (low) reading
    */
    float getWetValue();

    /** Return the ID of this sensor

    @return unsigned int ID of this sensor
    */
    unsigned int getId();

protected:
    float _minReading;
    float _maxReading;
    int _id;


private:
    static unsigned int _nextId;
    AnalogIn _pin;
    
    float mapAndClamp(float value);
};

#endif 