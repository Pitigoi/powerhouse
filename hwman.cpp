#include "hwman.h"


hwman::hwman()
{
	cpu = cpu::getInstance();
	mem::setTotal();
	mem::getHandles();

}

int hwman::getHandles()
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
	for (char* p = strchr(readingbuf, 'x'); p != nullptr; p = strchr(p + 1, 'x'))
		cnt++;
	char handle[5] = "";

	char* p = strchr(readingbuf, 'x');
	mem* memp = new mem();
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < 4; j++)
			handle[j] = p[j + 1];

		handle[4] = 0;
		status = memp->fillByHandle(handle);
		if (status != 0)
		{
			printf("aualeu");
		}
		hwman::mems.insert(memp);
		p = strchr(p + 1, 'x');
		//merge doar pentru ca avem 0x apoi handle
	}

	printf("Created process with pid %d\n%s\n", pid, childout);

	return 0;
}
