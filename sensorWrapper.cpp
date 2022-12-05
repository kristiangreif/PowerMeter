#include "sensor_wrapper.h"
#include "Wire.h"
#include "INA226.h"
#include <ArduinoJson.h>

#define VCC_REDUCTION 0.7084
#define SHUNT_RESISTANCE 0.6 //in milliohms

INA226 INA(0x40);

bool setupINA(){
    Wire.begin();
    if(!INA.begin()){
        return false;
    }
    INA.setAverage(4);

    return true;
}

float getVoltage(){
    return INA.getBusVoltage() / VCC_REDUCTION;
}

float getCurrent(){
    return INA.getShuntVoltage_mV() / SHUNT_RESISTANCE;
}

void processReadings(READINGS *readings, unsigned long *lastTime){
    readings->voltage = getVoltage();
    readings->current = getCurrent();
    readings->power = readings->voltage * readings->current;

    unsigned long now = millis();
    double dt = (now - *lastTime) / 3.6E6;
    *lastTime = now;

    readings->capacityAh = readings->capacityAh + (readings->current * dt);
    readings->capacityWh = readings->capacityWh + (readings->power * dt);
}

void convertToString(READINGS *readings){
    sprintf(readings->strVoltage, "%6.3fV", readings->voltage);
    sprintf(readings->strCurrent, "%6.2fA", readings->current); 
    sprintf(readings->strPower, "%5.0fW", readings->power);
    sprintf(readings->strCapacityAh, "%6.2fAh", readings->capacityAh);
    sprintf(readings->strCapacityWh, "%6.0fWh", readings->capacityWh);  
}

void convertToJSON(READINGS *readings, char *output){
    StaticJsonDocument<JSON_SIZE> doc;
    
    doc["voltage"] = readings->strVoltage;
    doc["current"] = readings->strCurrent;
    doc["power"] = readings->strPower;
    doc["capacityAh"] = readings->strCapacityAh;
    doc["capacityWh"] = readings->strCapacityWh;

    serializeJson(doc, output, JSON_SIZE);
}