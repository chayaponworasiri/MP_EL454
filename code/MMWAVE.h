#ifndef MMWAVE_H
#define MMWAVE_H

#include <ld2410.h>

#define RADAR_RX_PIN 16
#define RADAR_TX_PIN 17

class MMWaveSensor {
private:
    ld2410 radar;

public:
    void begin() {
        Serial1.begin(256000, SERIAL_8N1, RADAR_RX_PIN, RADAR_TX_PIN);
        delay(500);
        if (radar.begin(Serial1)) {
            Serial.println(F("LD2410 Ready"));
        }
    }

    void update() { 
        radar.read(); 
    }

    bool isTargetDetected() {
        if (radar.isConnected()) {
            if (radar.movingTargetDetected() && radar.movingTargetEnergy() > 20) {
                return true;
            }
        }
        return false; 
    }
};

#endif