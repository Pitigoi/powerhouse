#include"brightness.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define READ_END 0
#define WRITE_END 1

Bright::Bright()
{
	char* buff = (char*)malloc(sizeof(char)*128);
	int ok=readFromPipe("brightnessctl | egrep 'Current*' | cut -d' ' -f3,4", buff);

	if(ok!=0)
	{
		//LOGGER
		//return;
	}

	const char delim[]=" ()";

	char* token = strtok(buff, delim);
		
	this->nits=atoi(token);

	token=strtok(NULL, delim);

	this->value=(char*)malloc(sizeof(char)*strlen(token)+1);

	strcpy(this->value, token);

	token=NULL;
	free(buff);
	buff=NULL;

}

int Bright::getNits()
{
	return this->nits;
}

char* Bright::getValue()
{
	return this->value;
}

Bright::~Bright()
{
	free(this->value);
	value=NULL;
}

int Bright::readFromPipe(const char *command, char* str)
{
	int fd[2];
	pipe(fd);

	if (pipe(fd) < 0)
		printf("error : pipe\n");
	// TO DO : LOGGER MARK aand exit

	pid_t pid = fork();

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