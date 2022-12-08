#include "procman.h"

static procman* procman::getInstance()
{
	if (instance == nullptr)
	{
		instance = new procman;
	}
	return instance;
}

proc* procman::operator[](int index)
{
	if (index > size)
	{
		//eroare serioasa baga semnal SIGSEGV
	}
	return table[index];
}

proc* procman::operator[](int pid)
{
	setpoint i = set.find(pid);
	if (i == set::end)
		return nullptr;
	return i;
}

static void procman::updateList()
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
	char childout[512] = "";
	while (read(fd[0], readingbuf, 1) > 0)
	{
		strcat(childout, readingbuf);
	}
	close(fd[0]);
	int status;
	wait(pid, &status);

	for (setpoint i : set)
	{
		((proc*)i)->alive = false;
	}

	char* p = strtok(childout, "\n");
	int pid;
	do
	{
		sscanf(p, "%d", &pid);
		if (set[pid] != nullptr)
			((proc*)set[pid])->alive = true;
		else
			set.insert(proc(pid));
		((proc*)set[pid])->populatePid();

		p = strtok(NULL, "\n");
	} while (p != nullptr);

	for (setpoint i : set)
	{
		if (((proc*)i)->alive == false)
			set.erase(i);
	}


	printf("Created process with pid %d\n%s\n", pid, childout);

}