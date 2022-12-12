#include <stdio.h>

class GPU
{
private:
    int pid[50];
    float mib[50];
    int index;

    int getListOfProcesses();
    int isUsingGpu(int pid);
    int readFromPipe(const char *command, char* str);
    float convertMib(char* str);


public:
    GPU();
    ~GPU();
   
    float getMibOfProcess(int pid);
    int updateList();
};
