#include "procman.h"

procman* procman::instance=nullptr;
std::set<proc*> procman::set={};
procman::procman()
{

}

procman& procman::getInstance()
{
	if (instance == nullptr)
	{
		instance = new procman;
	}
	return *instance;
}

proc* procman::operator[](int pid)
{
	procpoint p=set.begin();
	for(p;p!=set.end();p++)
		if((*p)->pid==pid)
			break;
	if (p == set.end())
		return nullptr;
	return *p;
}
procman::~procman()
{
	instance = nullptr;
	set.clear();
}

void procman::updateList()
{
	int fd[2];
	if (pipe(fd) < 0)
		printf("error : pipe\n");
	int pid = fork();
	switch (pid) {
	case -1: /* fork failed */
		printf("error : fork\n");
		exit(EXIT_FAILURE);
	case 0: /* child process */
		close(fd[0]);
		dup2(fd[1], 1);
		execl("/bin/sh", "sh", "-c", "ps -eo pid | awk '{$1=$1};1' | head -n-4 | tail -n+2", (char*)NULL);
	}

	close(fd[1]);

	char readingbuf[2] = "a";
	int* pids=new int[100];
	int pidn=0;
	char childout[12] = "";
	while (read(fd[0], readingbuf, 1) > 0 && pidn<100-1)
	{
		strcat(childout, readingbuf);
		if(readingbuf[0]=='\n')
		{
			sscanf(childout,"%d",&(pids[pidn++]));
			strcat(childout,"");
		}
	}
	close(fd[0]);
	int status;
	wait(&status);

	for (proc* i : set)
	{
		((proc*)i)->alive = false;
	}
	for(int i=0;i<pidn;i++)
	{
		if ((*instance)[pids[i]] != nullptr)
			(*instance)[pids[i]]->alive = true;
		else
			set.insert(new proc(pids[i]));
		((*instance)[pids[i]])->populatePid();
	} 

	for (proc* i : set)
	{
		if (((proc*)i)->alive == false)
			set.erase(i);
	}

	//printf("Created process with pid %d\n%s\n", pid, childout);
}

void procman::print()
{
	for(auto a=set.begin();a !=set.end();a++)
	{
		printf("%d\t%s\t %f,%f,%f,%f\n",(*a)->pid,(*a)->command,(*a)->cpu_cons,(*a)->gpu_cons,(*a)->mem_cons,(*a)->total_cons);
	}
}