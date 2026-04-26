#ifndef GASMQ7_H
#define GASMQ7_H

#define PIN_MQ7 7

class GasSensor {
public:
    void begin() {
        pinMode(PIN_MQ7, INPUT);
    }

    int readRaw() {
        return analogRead(PIN_MQ7);
    }

    float getPPM() {
        int raw = readRaw();
        return map(raw, 0, 4095, 0, 1000); 
    }
};

#endif