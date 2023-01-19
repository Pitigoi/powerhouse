#include "gpu.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define READ_END 0
#define WRITE_END 1


bool GPU::smierr=false;
GPU* GPU::instance = nullptr;

GPU& GPU::getInstance()
{
    if(!GPU::instance)
    {
        GPU::instance = new GPU();
    }

    return (*GPU::instance);
}

void GPU::destroyInstance()
{
    if(GPU::instance)
    {
        GPU::getInstance().erase();
        delete GPU::instance;
        GPU::instance=nullptr;
    }
}

GPU::GPU()
{
    this->index=0;

    int ok=getListOfProcesses();
    if(ok!=0)
    {
        smierr=true;
        //TO DO LOGGER FAILED TO FETCH LIST OF PROC
    }
    if(!smierr)
        setTotalUsage();


}

float GPU::getTotalUsage()
{
    return totalUsage;
}

void GPU::setTotalUsage()
{
    char* buff =(char*)malloc(sizeof(char)*1024);
    this->readFromPipe("nvidia-smi -q | egrep \"FB\" -A 1 | egrep -o \" [0-9]* MiB\" | egrep -o \"[0-9]*\"", buff);
    if(strlen(buff)>0)
    this->totalUsage=atof(buff);
    else 
    this->totalUsage=0;


}

float GPU::getFromTurbostat()
{
    FILE* f= fopen("gpu_pck_wat.txt", "r");
	float total=0;
	char line[50];
	fgets(line, 50, f);
	for(int i=0;i<8;i++)
	{
		fgets(line, 20, f);
		line[strlen(line)-1] = '\0';
		total += atof(line);
	}

	float watts=total/8;

	fclose(f);

    return watts;
}


void GPU::setWatts()
{
    char* buff =(char*)malloc(sizeof(char)*1024);
    this->readFromPipe("nvidia-smi -q --display=\"VOLTAGE\" | egrep \"Graphics\" | tr -s \" *\" \" \" | cut -d\" \" -f4", buff);
    printf("%s", buff);
    if(buff[0]=='N')      
    {   
        this->watts=getFromTurbostat();
    }
    else{
        this->watts=atof(buff);
    }
}

float GPU::getWatts()
{
    return this->watts;
}

float GPU::getConsumptionOfProcess(int pid)
{
    if(smierr)return 0;
    
    
    int mib = getMibOfProcess(pid);
    if(mib == -1)
    {
        return 0;
    }

    
    float rez = (mib* watts)/totalUsage;    //deci procesul pid foloseste rez w 

    return rez;

}

int GPU::getIndex()
{
    return this->index;
}

int GPU::getListOfProcesses()
{
    memset(this->mib, 0, sizeof(this->mib));
    memset(this->pid, 0, sizeof(this->pid));
    index =0;
    
    char* buff =(char*)malloc(sizeof(char)*1024);
    int ok = readFromPipe("nvidia-smi | tail +19 | tr -s ' *' ' '", buff);
    if(ok!=0)
    {   
        //LOGGER
        return -1;
    }
    if(strlen(buff)==0)
    {
        //LOGGER
        free(buff);
        return -2;
    }

    const char delim[]=" \n";

    char* token=strtok(buff, delim);
    char* dup=strdup(buff);

    int cnt=1;

    while(token!=NULL)
    {
        token=strtok(NULL, delim);

        if(token[0] == '+')         //it reached end of list of processes
            break;

        if(cnt==4)
        {
            this->pid[this->index] = atoi(token);
            
        }

        if(cnt==7)
        {
            this->mib[this->index] = convertMib(token);
            this->index++;
        }

        if(dup[token-buff+strlen(buff)] == '\n')     //mark new line
        {
            cnt=1;
        }
        else
        {
            cnt++;
        }

    }

    free(dup);
    dup=NULL;

    return 0;

}

float GPU::convertMib(char* str)
{
    char* aux=(char*)malloc(sizeof(char) * strlen(str)+1);
    int cnt=0;

    for(int i=0;i<strlen(str);i++)
    {
        if(str[i] == 'M')
        {
            cnt=i;
            break;
        }
    }

    strncpy(aux, str, cnt);

    float rez=atof(aux);

    free(aux);
    aux=NULL;
    
    return rez;

}

int GPU::isUsingGpu(int pid)
{
    for (int i = 0; i < this->index; i++)
    {
        if (pid == this->pid[i])
            return i; // returns the index of the process
    }

    return -1;
}

float GPU::getMibOfProcess(int pid)
{
    int rez = isUsingGpu(pid);

    if (rez != -1)
    {
        return mib[rez];
    }

    return -1;
}

int GPU::readFromPipe(const char *command, char* str)
{
	int fd[2];
	pipe(fd);

	if (pipe(fd) < 0)
		printf("error : pipe\n");
	// TO DO : LOGGER MARK aand exit

	pid_t pid = fork();

	switch (pid)
	{
	case -1:
		// LOGGER
		printf("error : pipe\n");
		return -1;
	case 0:
		close(fd[READ_END]);
		dup2(fd[WRITE_END], 1);
		execl("/bin/sh", "sh","-c", command, (char*)NULL);
		return 0;
	default:
		close(fd[WRITE_END]);

		char readingbuf[2] = "a";
		char childout[512] = "";
		while (read(fd[READ_END], readingbuf, 1) > 0)
		{
			strcat(childout, readingbuf);
		}

		close(fd[READ_END]);
		int status;
		wait(&status);

		strcpy (str, childout);
		return 0;
	}

}


void GPU::erase()
{
    for(int i=0;i<index;i++)
    {
        this->pid[i]=0;
        this->mib[i]=0;
    }

    this->index=0;
}
