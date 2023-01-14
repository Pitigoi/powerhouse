#pragma once
#include <stdio.h>
#include <string.h>
#include "hwman.h"
class proc
{
protected:
	int pid;
	bool alive;
	char command[100];
	float cpu_cons;
	float gpu_cons;
	float mem_cons;
	float total_cons;
	friend bool operator<(const proc& a, const proc& b);
	proc(int pid) :pid(pid), alive(true)
	{
		strcpy(command, "");
		gpu_cons = cpu_cons = mem_cons = total_cons = 0;
	}
	friend class procman;
	friend bool operator< (const proc& a, const proc& b);
public:
	int populatePid();
};

