#pragma once
#include <stdio.h>

class GPU
{
private:
    float mib[50];
    int index;
    float totalUsage;
    float watts;
    int pid[50];
    static GPU* instance;
    GPU();
    GPU(const GPU&) {};
    ~GPU() {};

    int getListOfProcesses();
    int isUsingGpu(int pid);
    int readFromPipe(const char *command, char* str);
    float convertMib(char* str);
    void setTotalUsage();
    float getFromTurbostat();
public:
    static bool smierr;
    static GPU& getInstance();
    static void destroyInstance();
    
    float getConsumptionOfProcess(int pid);
    int getIndex();
    float getMibOfProcess(int pid);
    float getTotalUsage();
    void setWatts();
    float getWatts();
    void erase();
};
