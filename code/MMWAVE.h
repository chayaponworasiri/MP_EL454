#ifndef MMWAVE_H
#define MMWAVE_H

#include <Wire.h>

class MMWaveSensor {
public:
    bool begin() {
        return true; 
    }

    void update() {
    }
    
    bool isTargetDetected() {
        return false; 
    }
};

#endif