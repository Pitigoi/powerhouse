#include <stdio.h>

class Battery
{
private:
    float voltage;
    float current_energy;
    float time_to_empty;

    void setVoltage();
    void setCurrentEnergy();
    void setTimeToEmpty();

    void updateStats();

    char *readFromPipe(char *command);

public:
    Battery();
    ~Battery(){};
    // Battery(int v, int e, int t);

    float getVoltage();
    float getCurrentEnergy();
    float getTimeToEmpty();
};
