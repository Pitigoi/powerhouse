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

int Battery::readFromPipe(const char *command, char* str)
{
	int fd[2];
	pipe(fd);

	if (pipe(fd) < 0)
		printf("error : pipe\n");
	// TO DO : LOGGER MARK aand exit

	pid_t pid = fork();
	//printf("%d\n", pid);
	switch (pid)
	{
	case -1:
		// LOGGER
		printf("error : pipe\n");
		return -1;
	case 0:
		close(fd[READ_END]);
		dup2(fd[WRITE_END], 1);
		execl("/bin/sh", "sh","-c", command, (char*)NULL);
		return 0;
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

		strcpy (str, childout);
		return 0;
	}

	
}

void Battery::set(float* param, const char* command)
{
	char *buff = (char *)malloc(sizeof(char) * 200);
	int ok = readFromPipe(command, buff);
	if(ok != 0)
	{
		//TO DO: Logger check
		return;
	}

	 float volt = atof(buff);

	*param = volt;

	free(buff);
	buff=NULL;
}
/*
void Battery::setVoltage()
{
	char *v = (char *)malloc(sizeof(char) * 200);
	int ok = readFromPipe("upower -d | egrep -m1 'voltage:' | tr -s ' *' ' ' | cut -d' ' -f3 | tr -s ',' '.'", v);
	if(ok != 0)
	{
		//TO DO: Logger check
		return;
	}

	 float volt = atof(v);

	this->voltage = volt;

	free(v);
	v=NULL;
}

void Battery::setCurrentEnergy()
{
	char *e = (char *)malloc(sizeof(char) * 200);
	int ok= readFromPipe("upower -d | egrep -m1 'energy:' | tr -s ' *' ' ' | cut -d' ' -f3 | tr -s ',' '.'", e);
	if(ok != 0)
	{
		//TO DO: Logger check
		return;
	}

	float en = atof(e);

	this->current_energy = en;
	free(e);
	e=NULL;
}

void Battery::setTimeToEmpty()
{
	char *e = (char *)malloc(sizeof(char) * 200);
	int ok =readFromPipe("upower -d | egrep -m1 'time' | tr -s ' *' ' ' | cut -d' ' -f5 | tr -s ',' '.'", e);

	if(ok != 0)
	{
		//TO DO: Logger check
		return;
	}

	float en = atof(e);

	this->time_to_empty = en;

	free(e);
	e=NULL;
}
*/

Battery::Battery()
{
	this->voltage=0;
	this->current_energy=0;
	this->time_to_empty=0;

	this->set(&this->voltage, "upower -d | egrep -m1 'voltage:' | tr -s ' *' ' ' | cut -d' ' -f3 | tr -s ',' '.'");
	this->set(&this->current_energy, "upower -d | egrep -m1 'energy:' | tr -s ' *' ' ' | cut -d' ' -f3 | tr -s ',' '.'");
	this->set(&this->time_to_empty, "upower -d | egrep -m1 'time' | tr -s ' *' ' ' | cut -d' ' -f5 | tr -s ',' '.'");

}