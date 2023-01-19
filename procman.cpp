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
			return *p;
	return nullptr;
}
procman::~procman()
{
	instance = nullptr;
	set.clear();
}

void procman::updateList(float cpu, float gpu, float mem)
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
	int* pids=new int[1024];
	int pidn=0;
	char childout[12] = "";
	while (read(fd[0], readingbuf, 1) > 0 && pidn<1023)
	{
		strcat(childout, readingbuf);
		if(readingbuf[0]=='\n')
		{
			sscanf(childout,"%d",&(pids[pidn++]));
			strcpy(childout,"");
		}
	}
	close(fd[0]);
	int status;
	wait(&status);

	for (proc* i : set)
	{
		((proc*)i)->alive = false;
	}
	proc* n;

	for(int i=0;i<pidn;i++)
	{
		if ((*instance)[pids[i]] != nullptr)
			(*instance)[pids[i]]->alive = true;
		else
		{
			n=new proc(pids[i]);
			n->populatePid();
			n->setBatcons(cpu, gpu, mem);
			if(n!=nullptr && n->alive)
				set.insert(n);
			
		}
	} 

	for (proc* i : set)
	{
		if (i!=nullptr)
			if( ((proc*)i)->alive == false)
				set.erase(i);
	}

}

//
std::set<proc*> procman::getList()
{
	return this->set;
}

proc* procman::search_list(int pid)
{
	for(auto i=set.begin();i !=set.end();i++)
	{
		if((*i)->getPid() == pid)
			return (*i);
	}

	return nullptr;
}

void procman::print_by_pid(int pid)
{
	proc* temp=search_list(pid);
	if( temp != nullptr)
	{
		printf("%d\t %f | %f | %f | %f |\t%f |\t%s\n",temp->pid,temp->cpu_cons,temp->gpu_cons,temp->mem_cons,temp->total_cons,temp->bat_cons,temp->command);
	}
	else{
		printf("There isn't a procces with this pid in list\n");
	}
}

void procman::print()	
{
	for(auto a=set.begin();a !=set.end();a++)
	{
		printf("%d\t %f | %f | %f | %f |\t%f |\t%s\n",(*a)->pid,(*a)->cpu_cons,(*a)->gpu_cons,(*a)->mem_cons,(*a)->total_cons,(*a)->bat_cons,(*a)->command);
	}
}