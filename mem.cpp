#include "mem.h"

mem::mem() {

}

int mem::total()
{
	FILE* in = fopen("/proc/meminfo", "r");
	char a[100], b[100];
	fgets(a, 100, in);
	sscanf(a, "MemTotal:\t\t%d", total);
	fclose(in);
}

int mem::fillByHandle(char handle[5])
{
	mem out;

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
		execl("/bin/sh", "sh", "-c", "dmidecode -t 17", (char*)NULL);
		//"dmidecode -t 17 | grep -o \"Handle 0x....\""				
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

	//todo

	printf("Created process with pid %d\n%s\n", pid, childout);

	return out;
}


int mem::getHandles()
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
		execl("/bin/sh", "sh", "-c", "dmidecode -t 17", (char*)NULL);
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
	for (char* p i = strchr(readingbuf, 'x'); p != null; p = strchr(p + 1, 'x'))
		cnt++;
	char handle[5];

	char* p = strchr(readingbuf, 'x')
		for (int i = 0; i < cnt; i++)
		{
			for (int j = 0; j < 4; j++)
				handle[j] = p[j + 1];

			handle[j] = 0;
			status = fillByHandle(handle);
			if (status != 0)
			{
				printf("aualeu");
			}
			p = strchr(p + 1, 'x');
			//merge doar pentru ca avem 0x apoi handle
		}

	printf("Created process with pid %d\n%s\n", pid, childout);

	return out;
}