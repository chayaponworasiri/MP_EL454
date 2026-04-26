#ifndef IR_H
#define IR_H

#define PIN_IR 40

class IRSensor {
public:
    void begin() {
        pinMode(PIN_IR, INPUT);
    }

    bool isTriggered() {
        return digitalRead(PIN_IR) == LOW; 
    }
};

#endif