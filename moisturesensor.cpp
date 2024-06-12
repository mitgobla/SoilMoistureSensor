// Library for a Capacitive Soil Moisture Sensor
// Written by Ben Dodd (mitgobla)

#include "moisturesensor.h"

unsigned int MoistureSensor::_nextId = 0;

MoistureSensor::MoistureSensor(PinName analogIn) : _id(_nextId++), _pin(analogIn) {}

float MoistureSensor::mapAndClamp(float value) {
    if (value > _maxReading) {
        value = _maxReading;
    } else if (value < _minReading) {
        value = _minReading;
    }

    float mappedValue = 1.0f - (value - _minReading) / (_maxReading - _minReading);
    return mappedValue;
}

float MoistureSensor::getRawReading() {
    return _pin.read();
}

float MoistureSensor::getClampedReading() {
    return mapAndClamp(getRawReading());
}

void MoistureSensor::setDryValue() {
    _maxReading = getRawReading();
}

void MoistureSensor::setWetValue() {
    _minReading = getRawReading();
}

float MoistureSensor::getDryValue() {
    return _maxReading;
}

float MoistureSensor::getWetValue() {
    return _minReading;
}

unsigned int MoistureSensor::getId() {
    return _id;
}

