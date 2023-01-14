#pragma once
#include <stdio.h>

class GPU
{
private:
    
    float mib[50];
    int index;
    float totalUsage;
    int pid[50];

    int getListOfProcesses();
    int isUsingGpu(int pid);
    int readFromPipe(const char *command, char* str);
    float convertMib(char* str);
    void setTotalUsage();
public:
    GPU();
    ~GPU();
    float getConsumptionOfProcess(int pid);
    int getIndex();
    float getMibOfProcess(int pid);
    float getTotalUsage();
};
