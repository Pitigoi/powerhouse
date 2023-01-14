#pragma once
#include <cstdio>
#include <cstring>
class cpu 
{
private:
	cpu();
	static cpu* instance;

	cpu(const cpu& oth) = delete;
	cpu& operator=(const cpu& oth) = delete;
protected:
friend class hwman;
	static int id;
	static char name[100];
	static float freq;
	static int cachesize;
	static int cpuinfo();
public:
	~cpu();
	static cpu* getInstance();
};

