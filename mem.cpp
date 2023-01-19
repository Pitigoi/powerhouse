#include "mem.h"
#include <sys/wait.h>

int mem::total=0;

mem::mem() {
	cachesize = 0;
	strcpy(name,"");
	freq = 0;
	setTotal();
	setPckWatts();
}

void mem::setTotal()
{
	FILE* in = fopen("/proc/meminfo", "r");
	char a[100];
	fgets(a, 100, in);
	sscanf(a, "MemTotal:\t\t%d", &total); //nr intreg in kb
	fclose(in);
}

void mem::setPckWatts()
{
	FILE* f= fopen("mem_pck_wat.txt", "r");
	float total=0;
	char line[50];
	fgets(line, 50, f);
	for(int i=0;i<14;i++)
	{
		fgets(line, 20, f);
		line[strlen(line)-1] = '\0';
		total += atof(line);
	}

	this->average=total/14;

	fclose(f);
}

float mem::getAverage()
{
	return this->average;
}

int mem::fillByHandle(char handle[5])
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
		char command[] = "dmidecode -H 0x001B";
		strcpy(command + 15, handle);
		close(fd[0]);
		dup2(fd[1], 1);
		execl("/bin/sh", "sh", "-c", command, (char*)NULL);		
	}

	close(fd[1]);

	char readingbuf[2] = "a";
	char childout[512] = "";
	while (read(fd[0], readingbuf, 1) > 0)
	{
		strcat(childout, readingbuf);
	}
	close(fd[0]);
	int status;
	wait(&status);

	char* p;

	//	Type: DDR4
	p=strstr(childout, "\tType: ");
	sscanf(p,"\tType: %9s\n",type);

	//	Speed : 3200 MT / s
	p=strstr(childout, "\tSpeed : ");
	sscanf(p,"\tSpeed : %d MT / s\n", &freq);

	//	Part Number : 8ATF2G64HZ - 3G2E2
	p=strstr(childout, "\tPart Number : ");
	sscanf(p, "\tPart Number : %99s\n",name);

	//	Configured Voltage : 1.2 V
	p=strstr(childout, "\t Configured Voltage : ");
	sscanf(p, "\t Configured Voltage : %f V\n",&voltage);

	//	Volatile Size : 16 GB
	p=strstr(childout, "\tVolatile Size : ");
	sscanf(p, "\tVolatile Size : %d GB\n",&cachesize);

	//printf("Created process with pid %d\n%s\n", pid, childout);

	return 0;
}


