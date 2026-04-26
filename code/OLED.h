#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

class MyOLED {
public:
    Adafruit_SSD1306 display;

    MyOLED() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

    bool begin() {
        if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
            return false;
        }
        
        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(1);
        display.setCursor(0,0);
        display.println("System Starting...");
        display.display();
        return true;
    }

    void updateDashboard(float temp, int gas, bool ir, bool mmwave, bool clap) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0,0);
        
        display.printf("TEMP: %.1f C\n", temp);
        display.printf("GAS : %d PPM\n", gas);
        display.printf("IR  : %s\n", ir ? "DETECTED" : "-");
        
        // ส่วนที่เน้น: แสดงสถานะการเจอคนจาก mmWave
        display.printf("MOVE: %s\n", mmwave ? "FOUND PERSON" : "NO ONE"); 
        
        display.printf("CLAP: %s\n", clap ? "YES!" : "-");
        
        display.display();
    }

    void clear() {
        display.clearDisplay();
        display.display();
    }
};

#endif