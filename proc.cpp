#include "proc.h"
#include <stdlib.h>

int proc::populatePid()
{

	int fd[2];
	if (pipe(fd) < 0)
		printf("error : pipe\n");

	int pid2 = fork();
		char comm[64] ="";
		sprintf(comm,"ps -p%d", pid);
	switch (pid2) {
	case -1: /* fork failed */
		printf("error : fork\n");
		exit(EXIT_FAILURE);
	case 0: /* child process */
		close(fd[0]);
		dup2(fd[1], 1);
		strcat(comm," -o %cpu,%mem,comm | awk '{$1=$1};1' | tail -n+2");
		execl("/bin/sh", "sh", "-c", comm, (char *) NULL);
		exit(1);
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

	int cnt = 0;
	for (char* p = strchr(childout, '\n'); p != nullptr; p = strchr(p + 1, '\n'))
		cnt++;
	//adg un endl pt sscanf
	childout[strlen(childout) + 1] = 0;
	childout[strlen(childout)] = '\n';
	sscanf(childout, "%f %f %99[^\n]",&cpu_cons,&mem_cons,command);
	cpu_cons*=hwman::nominalconsCPU()/100.0;
	mem_cons*= hwman::nominalconsMEMS() / 100.0;
	if(GPU::smierr)
	gpu_cons = hwman::gpucons(pid);
	total_cons=cpu_cons+mem_cons+gpu_cons;
	if(total_cons==0)alive=false;
	//printf("Created process with pid %d\n%s\n", pid2, childout);
	return 0;
}

bool operator< (const proc& a, const proc& b)
{
	return a.pid<b.pid;
}