#include "cpu.h"

char cpu::name[100]="";
float cpu::freq=0;
int cpu::id=0;
int cpu::cachesize=0;

cpu* cpu::instance = nullptr;

cpu::cpu()
{
}

cpu::~cpu()
{
	instance = nullptr;
	id = cachesize = 0;
	freq = 0;
	strcpy(name, "");
}

cpu* cpu::getInstance()
{
	if (instance == nullptr)
	{
		instance = new cpu;
		int status = cpu::cpuinfo();
		if (status != 0)
		{
			printf("opa");
		}
	}
	return instance;
}

int cpu::cpuinfo()
{
	FILE* in = fopen("/proc/cpuinfo", "r");

	char a[100];
	fgets(a, 100, in);
	sscanf(a, "processor\t: %d", &id);//id

	for (int i = 0; i < 4; i++)
		fgets(a, 100, in);
	a[strlen(a) - 1] = '\0';
	strcpy(name, a + 13);//name

	for (int i = 0; i < 2; i++)
		fgets(a, 100, in);

	sscanf(a, "cpu MHz\t\t: %f", &freq);//freq
	fgets(a, 100, in);

	sscanf(a, "cache size\t: %d", &cachesize);//cachesize
	fclose(in);
	return 0;
}
