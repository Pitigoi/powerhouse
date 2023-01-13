#include <stdio.h>

class GPU
{
private:
    
    float mib[50];
    int index;
    float totalUsage;

    int getListOfProcesses();
    int isUsingGpu(int pid);
    int readFromPipe(const char *command, char* str);
    float convertMib(char* str);
    void setTotalUsage();
    
    


public:
    GPU();
    ~GPU();
    int pid[50];
    
    float getConsumptionOfProcess(int pid);
    int getIndex();
    float getMibOfProcess(int pid);
    int updateList();
    float getTotalUsage();
};
