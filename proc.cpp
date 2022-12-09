#include "proc.h"

int proc::populatePid()
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

		execl("/bin/sh", "sh", "-c", "ps -p pidul -o %cpu,%mem,comm | awk '{$1=$1};1' | tail -n+2", (char*)NULL);
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

	int cnt = 0;
	for (char* p = strchr(readingbuf, '\n'); p != nullptr; p = strchr(p + 1, '\n'))
		cnt++;
	
	//de verif astea
	readingbuf[strlen(readingbuf) + 1] = 0;
	readingbuf[strlen(readingbuf)] = '\n';
	//sscanf(readingbuf, "%f %f %s\n",cpu_cons,mem_cons,command);
	sscanf(readingbuf, "%f %f %99[^\n]",cpu_cons,mem_cons,command);

	printf("Created process with pid %d\n%s\n", pid, childout);
	return 0;
}

bool operator< (const proc& a, const proc& b)
{
	return a.pid<b.pid;
}