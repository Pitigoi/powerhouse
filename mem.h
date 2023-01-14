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
	friend class hwman;
	static int total;
	char name[100];
	char type[10];
	int freq;
	int cachesize;
	float voltage;
public:
	static void setTotal();

	mem();
	int fillByHandle(char handle[5]);
};

