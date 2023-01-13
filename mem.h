#pragma once
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>

class mem
{
private:
protected:
	mem();
	friend class hwman;
	static int total;
	char name[100];
	char type[10];
	float freq;
	int cachesize;
	float voltage;
public:
	static int setTotal();

	int fillByHandle(char handle[5]);
};

