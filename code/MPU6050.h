#ifndef MPU6050_H
#define MPU6050_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class MyMPU6050 {
    Adafruit_MPU6050 mpu;
public:
    bool begin() {
        if (!mpu.begin(0x68, &Wire)) {
            return false;
        }
        mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
        mpu.setGyroRange(MPU6050_RANGE_500_DEG);
        mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
        return true;
    }

    void getReading(sensors_event_t &a, sensors_event_t &g, sensors_event_t &temp) {
        mpu.getEvent(&a, &g, &temp);
    }
};

#endif