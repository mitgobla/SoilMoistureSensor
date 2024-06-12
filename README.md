# Soil Moisture Sensor

Library for using a Capacitive Soil Moisture sensor (or any analog compatible sensor) on Mbed OS 6.

![Soil Moisture Sensor](https://europe1.discourse-cdn.com/arduino/optimized/4X/b/f/5/bf59c155277511be834da260534b8200200ebebe_2_500x500.jpeg)

* `MoistureSensor` is a basic setup for setting a dry reading and wet reading, and then reading a value first mapped between the dry and wet and then clamped between 0.0 (dry) and 1.0 (wet).
* `FileBackedMoistureSensor` provides support to save dry and wet values to a file system so that they can be restored on program restart. Needs to be `setup()` first.

## Example Usage

Note: To print floats on mbed, ensure `mbed_app.json` has
```json
{
    "target_overrides": {
        "*": {
            "platform.minimal-printf-enable-floating-point": true
        }
    }
}
```

### `MoistureSensor`

```cpp
#include "mbed.h"
#include "moisturesensor.h"

// Analog Input pin
PinName analogPin(ARDUINO_UNO_A0);

MoistureSensor sensor(analogPin);

int main()
{
    printf("Have sensor dry to calibrate dry reading.\r\n");
    ThisThread::sleep_for(5s);
    sensor.setDryValue();
    printf("Dry calibration: %.2f\r\n", sensor.getDryValue());

    printf("Now put sensor into water to calibrate wet reading.");
    ThisThread::sleep_for(5s);
    sensor.setWetValue();
    printf("Wet calibration: %.2f\r\n", sensor.getWetValue());

    while (true) {
        // Clamped returns reading between 0.0 (dry) and 1.0 (wet)
        // Multiply by 100 to turn into percentage.
        printf("Current reading: %.2f%%", sensor.getClampedReading() * 100);
        ThisThread::sleep_for(1s);
    }
}
```

### `FileBackedMoistureSensor`

```cpp
#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
#include "filebackedmoisturesensor.h"

// Setup file system with SD card
SDBlockDevice sd(PTE3, PTE1, PTE2, PTE4);
FATFileSystem fs("fs");

// Analog Input pin
PinName analogPin(ARDUINO_UNO_A0);

FileBackedMoistureSensor sensor(analogPin);

// Use button to start calibration process
InterruptIn button(SW2);
volatile bool isButtonPressed = false;

void buttonPressed() {
    isButtonPressed = true;
}

// Calibration method that gets triggered after button is pressed.
void calibrateSensor() {
    printf("Have sensor dry to calibrate dry reading.\r\n");
    ThisThread::sleep_for(5s);
    sensor.setDryValue();
    printf("Dry calibration: %.2f\r\n", sensor.getDryValue());
    printf("Now put sensor into water to calibrate wet reading.");
    ThisThread::sleep_for(5s);
    sensor.setWetValue();
    printf("Wet calibration: %.2f\r\n", sensor.getWetValue());
    isButtonPressed = false;
}

int main()
{
    // FileBackedMoistureSensor must be setup before running.
    // This creates (or reads) its binary file on the SD card.
    sensor.setup();

    // Button updates boolean
    button.fall(&buttonPressed);

    while (true) {
        if (isButtonPressed) {
            calibrateSensor();
        }

        // Clamped returns reading between 0.0 (dry) and 1.0 (wet)
        // Multiply by 100 to turn into percentage.
        printf("Current reading: %.2f%%", sensor.getClampedReading() * 100);
        ThisThread::sleep_for(1s);
    }
}
```
