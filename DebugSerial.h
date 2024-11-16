#ifndef DEBUGSERIAL_H
#define DEBUGSERIAL_H

#include <Arduino.h>

class DebugSerial {
public:

    void begin(long baudRate) {
        Serial.begin(baudRate);
    }

    void print(const String &message) {
        Serial.print(message);
    }

    void println(const String &message) {
        Serial.println(message);
    }

    void print(float value) {
        Serial.print(value);
    }

    void println(float value) {
        Serial.println(value);
    }
};

#endif // DEBUGSERIAL_H
