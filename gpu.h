#include <stdio.h>

class GPU
{
private:
    int pid[50];
    int mib[50];
    int num;
    int getListOfProcesses();

public:
    GPU();
    ~GPU(){};
    int isUsingGpu(int pid);
    int getMibOfProcess(int pid);
};
