#pragma once
#include <stdio.h>
#include <string.h>
class process 
{
protected:
	int pid;
	bool alive;
	char command[100];
	float cpu_cons;
	float mem_cons;
	//float gpu_cons;
	friend bool operator< (const proc& a, const proc& b);
	process(int pid) :pid(pid), alive(true)
	{

	}
	//int consum;//=medie ponderata consum nominal celelalte componente
public:

	void print()
	{
		printf
	}
	
	static void getPids();

	int populatePid()
	{

	}
};

