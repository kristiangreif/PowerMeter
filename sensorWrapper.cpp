#include "sensor_wrapper.h"
#include "Wire.h"
#include "INA226.h"
#include <ArduinoJson.h>

#define VCC_REDUCTION 0.7084
#define SHUNT_RESISTANCE 0.6 //in milliohms
#define RAW_SETTINGS_SIZE 192

INA226 INA(0x40);
LIMITS limits;

bool setupINA(){
    Wire.begin();
    if(!INA.begin()){
        Serial.println("Could not init INA226");
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

    sprintf(readings->strVoltage, "%6.3fV", readings->voltage);
    sprintf(readings->strCurrent, "%6.2fA", readings->current); 
    sprintf(readings->strPower, "%5.0fW", readings->power);
    sprintf(readings->strCapacityAh, "%6.2fAh", readings->capacityAh);
    sprintf(readings->strCapacityWh, "%6.0fWh", readings->capacityWh); 
}

void serializeReadings(READINGS *readings, char *output){
    DynamicJsonDocument doc(JSON_SIZE);
    
    doc["voltage"] = readings->strVoltage;
    doc["current"] = readings->strCurrent;
    doc["power"] = readings->strPower;
    doc["capacityAh"] = readings->strCapacityAh;
    doc["capacityWh"] = readings->strCapacityWh;

    serializeJson(doc, output, JSON_SIZE);
}

void updateLimits(char *message){
    DynamicJsonDocument doc(RAW_SETTINGS_SIZE);
    deserializeJson(doc, message);

    limits.lowVoltageLimitEnabled = doc["uvlimit"][0];
    limits.highVoltageLimitEnabled = doc["ovlimit"][0];
    limits.overCurrentLimitEnabled = doc["ovclimit"][0];
    limits.overPowerLimitEnabled = doc["ovplimit"][0];

    limits.lowVoltageLimit = doc["uvlimit"][1];
    limits.highVoltageLimit = doc["ovlimit"][1];
    limits.overCurrentLimit = doc["ovclimit"][1];
    limits.overPowerLimit = doc["ovplimit"][1];
}

void resetLimits(){
    limits.lowVoltageLimitEnabled = false;
    limits.highVoltageLimitEnabled = false;
    limits.overCurrentLimitEnabled = false;
    limits.overPowerLimitEnabled = false;

    limits.lowVoltageLimit = 0.0;
    limits.highVoltageLimit = 0.0;
    limits.overCurrentLimit = 0.0;
    limits.overPowerLimit = 0.0;
}

bool protectionTriggered(READINGS *readings){
    if(limits.lowVoltageLimitEnabled){
        if(readings->voltage < limits.lowVoltageLimit){
            return true;
        }
    }

    if(limits.highVoltageLimitEnabled){
        if(readings->voltage > limits.highVoltageLimit){
            return true;
        }
    }

    if(limits.overCurrentLimitEnabled){
        if(readings->current > limits.overCurrentLimit){
            return true;
        }
    }

    if(limits.overPowerLimitEnabled){
        if(readings->power > limits.overPowerLimit){
            return true;
        }
    }

    return false;

}