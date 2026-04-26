#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ตั้งค่าขนาดหน้าจอ
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
        
        display.printf("Temp: %.1f C\n", temp);
        display.printf("Gas : %d PPM\n", gas);
        display.printf("IR  : %s\n", ir ? "DETECT" : "CLEAR");
        display.printf("Move: %s\n", mmwave ? "YES" : "NO");
        display.printf("Clap: %s\n", clap ? "DETECTED" : "-");
        
        display.display();
    }

    void clear() {
        display.clearDisplay();
        display.display();
    }
};

#endif