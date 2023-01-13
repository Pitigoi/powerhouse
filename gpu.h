#include <stdio.h>
#include "proc.h"

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
    
protected:

    friend int proc::populatePid();
    float getConsumptionOfProcess(int pid);


public:
    GPU();
    ~GPU();
    
    int getIndex();
    float getMibOfProcess(int pid);
    float getTotalUsage();
};
