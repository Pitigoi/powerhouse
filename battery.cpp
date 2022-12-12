#include "battery.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define READ_END 0
#define WRITE_END 1

float Battery::getVoltage()
{
	return this->voltage;
}

float Battery::getCurrentEnergy()
{
	return this->current_energy;
}

float Battery::getTimeToEmpty()
{
	return this->time_to_empty;
}

char *Battery::readFromPipe(char *command)
{
	int fd[2];
	pipe(fd);

	if (pipe(fd) < 0)
		printf("error : pipe\n");
	// TO DO : LOGGER MARK aand exit

	pid_t pid = fork();
	printf("%d\n", pid);
	switch (pid)
	{
	case -1:
		// LOGGER
		printf("error : pipe\n");
		exit(EXIT_FAILURE);
	case 0:
		close(fd[READ_END]);
		dup2(fd[WRITE_END], 1);
		execl(command, (char *)NULL);
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
	}
}

void Battery::setVoltage()
{
	char *v = (char *)malloc(sizeof(char) * 20);
	strcpy(v, readFromPipe("\"upower -d | egrep -m1 'voltage:' | tr -s ' *' ' ' | cut -d' ' -f3 | tr -s ',' '.'\""));

	printf("%s", v);

	// float volt = atof(v);

	// this->voltage = volt;
}

void Battery::setCurrentEnergy()
{
	char *e = (char *)malloc(sizeof(char) * 20);
	strcpy(e, readFromPipe("\"upower -d | egrep -m1 'energy:' | tr -s ' *' ' ' | cut -d' ' -f3 | tr -s ',' '.'\""));

	printf("%s", e);

	float en = atof(e);

	this->current_energy = en;
}

void Battery::setTimeToEmpty()
{
	char *e = (char *)malloc(sizeof(char) * 20);
	strcpy(e, readFromPipe("\"upower -d | egrep -m1 'time' | tr -s ' *' ' ' | cut -d' ' -f5 | tr -s ',' '.'\""));

	printf("%s", e);

	float en = atof(e);

	this->current_energy = en;
}

Battery::Battery()
{
	this->setCurrentEnergy();
	// this->setVoltage();
	// this->setTimeToEmpty();
}