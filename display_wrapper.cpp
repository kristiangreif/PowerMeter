#include "display_wrapper.h"
#include "fonts.h"
#include "SSD1306Wire.h"

SSD1306Wire display(0x3c, SDA, SCL);

void initDisplay(){
    display.init();
    display.flipScreenVertically();
}

void welcomeScreen(){
    display.clear();

    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(Dialog_bold_16);
    display.drawString(64, 0, "PowerMeter");
    display.setFont(Dialog_plain_12);
    display.drawString(64, 20, "Long press to start");
    display.drawString(64, 40, "Connect via WiFi");

    display.display();
}

void basicsScreen(char *voltage, char *current, char *power) {
    display.clear();

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(Dialog_plain_12);
    display.drawString(0, 1, "Voltage:");
    display.drawString(0, 22, "Current:");
    display.drawString(0, 43, "Power:");

    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.setFont(Dialog_bold_16);
    display.drawString(128, 0, voltage);
    display.drawString(128, 21, current);
    display.drawString(128, 42, power);

    display.display();
}

void capacityScreen(char *capacityAh, char *capacityWh) {
    display.clear();

    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(Dialog_plain_12);
    display.drawString(64, 1, "Capacity");

    display.setFont(Dialog_bold_16);
    display.drawString(64, 21, capacityAh);
    display.drawString(64, 42, capacityWh);

    display.display();
}

void displayScreen(byte n, READINGS *readings){
    switch (n){
        case 0:
            basicsScreen(readings->strVoltage, readings->strCurrent, readings->strPower);
            break;
        
        case 1:
            capacityScreen(readings->strCapacityAh, readings->strCapacityWh);
            break;
    }
}