// Library for a Capacitive Soil Moisture Sensor
// This sensor stores its calibration files to disk so that its state can be restored later.
// Written by Ben Dodd (mitgobla)

#include "filebackedmoisturesensor.h"
#include <cstdio>

FileBackedMoistureSensor::FileBackedMoistureSensor(PinName analogIn, const char* path) : MoistureSensor(analogIn), _path(path), _setup(false) {}

void FileBackedMoistureSensor::setup() {
    sprintf(_filepath, "%ssensor_%d.bin", _path, _id);
    FILE *file = fopen(_filepath, "rb");
    if (file != NULL) {
        if (fread(&_minReading, sizeof(_minReading), 1, file) < 1 ||
        fread(&_maxReading, sizeof(_maxReading), 1, file) < 1) {
            _minReading = 0.0;
            _maxReading = 1.0;
        }
        fclose(file);
    }
    _setup = true;
}

void FileBackedMoistureSensor::setDryValue() {
    MoistureSensor::setDryValue();
    saveValues();
}

void FileBackedMoistureSensor::setWetValue() {
    MoistureSensor::setWetValue();
    saveValues();
}

void FileBackedMoistureSensor::saveValues() {
    confirmSetup();
    FILE *file = fopen(_filepath, "wb");
    if (file != NULL) {
        fwrite(&_minReading, sizeof(_minReading), 1, file);
        fwrite(&_maxReading, sizeof(_maxReading), 1, file);
        fclose(file);
    }
}

void FileBackedMoistureSensor::confirmSetup() {
    if (!_setup) {
        error("Sensor %d was not setup. Run `setup()` after creating a filesystem.", _id);
    }
}

