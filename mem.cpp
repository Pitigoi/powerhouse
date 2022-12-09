#include "mem.h"

mem::mem() {
	total = 0;
	cachesize = 0;
	strcpy(name,"");
	freq = 0;
	int ;
	int ;
}

int mem::setTotal()
{
	FILE* in = fopen("/proc/meminfo", "r");
	char a[100];
	fgets(a, 100, in);
	sscanf(a, "MemTotal:\t\t%d", total); //nr intreg in kb
	fclose(in);
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
	wait(pid, &status);

	char* p;

	//	Type: DDR4
	p=strstr(childout, "\tType: ");
	sscanf(p,"\tType: %9s\n",type);

	//	Speed : 3200 MT / s
	//mt/s direct mhz
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

	printf("Created process with pid %d\n%s\n", pid, childout);

	return 0;
}


