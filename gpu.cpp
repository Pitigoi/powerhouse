#include "gpu.h"

GPU::GPU()
{
}

int GPU::isUsingGpu(int pid)
{
    for (int i = 0; i < num; i++)
    {
        if (pid == this->pid[i])
            return i; // returns the index of the process
    }

    return -1;
}

int GPU::getMibOfProcess(int pid)
{
    int rez = isUsingGpu(pid);

    if (rez != -1)
    {
        return mib[rez];
    }

    return -1;
}