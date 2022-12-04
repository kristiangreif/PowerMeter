#include "display_wrapper.h"
#include "fonts.h"
#include "SSD1306Wire.h"

#define MAX_VALUE_LENGTH 9

SSD1306Wire display(0x3c, SDA, SCL);

void initDisplay(){
    display.init();
    display.flipScreenVertically();
}

void basicsScreen(float voltage, float current, float power) {
    char *strVoltage, *strCurrent, *strPower;
    strVoltage = (char*) malloc(MAX_VALUE_LENGTH);
    strCurrent = (char*) malloc(MAX_VALUE_LENGTH);
    strPower = (char*) malloc(MAX_VALUE_LENGTH);

    sprintf(strVoltage, "%6.3fV", voltage);
    sprintf(strCurrent, "%6.2fA", current); 
    sprintf(strPower, "%5.0fW", power); 

    display.clear();

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(Dialog_plain_12);
    display.drawString(0, 1, "Voltage:");
    display.drawString(0, 22, "Current:");
    display.drawString(0, 43, "Power:");

    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.setFont(Dialog_bold_16);
    display.drawString(128, 0, strVoltage);
    display.drawString(128, 21, strCurrent);
    display.drawString(128, 42, strPower);

    display.display();

    free(strVoltage);
    free(strCurrent);
    free(strPower);
}

void capacityScreen(float capacityAh, float capacityWh) {
    char *strCapacityAh, *strCapacityWh;
    strCapacityAh = (char*) malloc(MAX_VALUE_LENGTH);
    strCapacityWh = (char*) malloc(MAX_VALUE_LENGTH);

    sprintf(strCapacityAh, "%6.2fAh", capacityAh);
    sprintf(strCapacityWh, "%6.0fWh", capacityWh);  

    display.clear();

    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(Dialog_plain_12);
    display.drawString(64, 1, "Capacity");

    display.setFont(Dialog_bold_16);
    display.drawString(64, 21, strCapacityAh);
    display.drawString(64, 42, strCapacityWh);

    display.display();

    free(strCapacityAh);
    free(strCapacityWh);
}