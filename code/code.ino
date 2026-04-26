#include <Wire.h>
#include "INMP441.h"
#include "MPU6050.h"
#include "GASMQ7.h"
#include "IR.h"
#include "MMWAVE.h"
#include "OLED.h"

MyOLED     myDisplay;
MyMPU6050  myMPU;
GasSensor  myGas;
IRSensor   myIR;
MMWaveSensor myMMWave;

TaskHandle_t ClapTaskHandle = NULL;
TaskHandle_t SensorTaskHandle = NULL;

void clapDetectionTask(void *pvParameters) {
    size_t bytesRead;
    while (true) {
        i2s_read(I2S_NUM_0, soundBuffer, sizeof(soundBuffer), &bytesRead, portMAX_DELAY);
        int maxAmp = 0;
        for (int i = 0; i < (bytesRead / 2); i++) {
            int amp = abs(soundBuffer[i]);
            if (amp > maxAmp) maxAmp = amp;
        }

        unsigned long now = millis();
        if (maxAmp > CLAP_THRESHOLD && (now - lastClapTime > CLAP_COOLDOWN)) {
            lastClapTime = now;
            Serial.printf("[CORE 0] Detected Clap! Amp: %d\n", maxAmp);
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void sensorUpdateTask(void *pvParameters) {
    while (true) {
        myMMWave.update(); 

        sensors_event_t a, g, temp;
        myMPU.getReading(a, g, temp);
        int gasPPM = myGas.readRaw();
        bool irState = myIR.isTriggered();
        
        bool moveState = myMMWave.isTargetDetected();

        myDisplay.updateDashboard(
            temp.temperature, 
            gasPPM, 
            irState, 
            moveState, 
            (millis() - lastClapTime < 500)
        );

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
void setup() {
    Serial.begin(115200);

    Wire.begin(8, 9); 

    initI2S();
    if(!myDisplay.begin()) Serial.println("OLED Failed!");
    if(!myMPU.begin())     Serial.println("MPU6050 Failed!");
    myGas.begin();
    myIR.begin();
    myMMWave.begin();

    xTaskCreatePinnedToCore(clapDetectionTask, "ClapTask", 4096, NULL, 2, &ClapTaskHandle, 0);

    xTaskCreatePinnedToCore(sensorUpdateTask, "SensorTask", 4096, NULL, 1, &SensorTaskHandle, 1);

    Serial.println("RTOS System Ready...");
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}