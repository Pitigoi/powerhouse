#pragma once
#include <stdio.h>

class Battery
{
private:

    static Battery* instance;
    float voltage;
    float current_energy;
    float time_to_empty;

    Battery() {};
    Battery(const Battery&){};
    ~Battery(){};

   // void setVoltage();
   // void setCurrentEnergy();
   // void setTimeToEmpty();
    void set(float* param, const char* command);

    //void updateStats();

    int readFromPipe(const char *command, char* str);

public:
    static Battery& getInstance();
    static void destroyInstance();

    void refresh();
    float getVoltage();
    float getCurrentEnergy();
    float getTimeToEmpty();
};
