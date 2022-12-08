#pragma once
#include <stdio.h>
#include <string.h>
class proc
{
protected:
	int pid;
	bool alive;
	char command[100];
	float cpu_cons;
	float mem_cons;
	//float gpu_cons;
	friend bool operator<(const proc& a, const proc& b);
	proc(int pid) :pid(pid), alive(true)
	{

	}
	friend class procman;
	//int consum;//=medie ponderata consum nominal celelalte componente
public:

	
	static void getPids();

	int populatePid()
	{

	}
};

