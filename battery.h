#pragma once
#include <stdio.h>

class Battery
{
private:
    float voltage;
    float current_energy;
    float time_to_empty;

   // void setVoltage();
   // void setCurrentEnergy();
   // void setTimeToEmpty();
    void set(float* param, const char* command);

    //void updateStats();

    int readFromPipe(const char *command, char* str);

public:
    Battery();
    ~Battery(){};

    void refresh();
    float getVoltage();
    float getCurrentEnergy();
    float getTimeToEmpty();
};
