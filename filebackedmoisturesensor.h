// Library for a Capacitive Soil Moisture Sensor
// This sensor stores its calibration files to disk so that its state can be restored later.
// Written by Ben Dodd (mitgobla)

#ifndef MBED_FILEBACKED_MOISTURE_SENSOR_H
#define MBED_FILEBACKED_MOISTURE_SENSOR_H

#include "moisturesensor.h"

class FileBackedMoistureSensor : public MoistureSensor {
public:
    /**
    Create a FileBackedMoistureSensor object connected to an analog input pin and optionally a filepath.
    *
    * @param analogIn pin connected to analog out pin on sensor.
    * @param path optional path for storing the calibrated values.
    */
    FileBackedMoistureSensor(PinName analogIn, const char* path = "/fs/");

    /**
    Setup this FileBackedMoistureSensor by writing the calibration to file if it doesn't exist already.
    Otherwise read the values if the file already exists.
    */
    void setup();

    /** Set the dry (high) value in which the clamped reading
    will be set to if the raw reading is above this value.

    It is saved to the file so that it does not need to be set again later.
    */
    void setDryValue() override;

    /** Set the wet (low) value in which the clamped reading
    will be set to if the raw reading is below this value.

    It is saved to the file so that it does not need to be set again later.
    */
    void setWetValue() override;

private:
    const char* _path;

    char _filepath[25];
    bool _setup;

    void saveValues();
    void confirmSetup();
};

#endif