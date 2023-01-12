#pragma once
#include <cstdio>
#include <cstring>
#include <unistd.h>//nu au echivalent in c++ deoarece nu sunt incluse in standard c ci in os
#include <cstdlib>
#include <sys/types.h>//same
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

