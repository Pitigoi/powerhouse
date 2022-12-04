#pragma once
#include <stdio.h>
#include <string.h>
class cpu 
{
protected:
	int id;
	char name[100];
	float freq;
	int cachesize;
	//int consum;
public:
	cpu()
	{
		//cpuinfo();
	}
	/*Intel Low End CPU (Core i3) 55 to 73 W
	Intel Mid End CPU (Core i5) 73 to 95 W
	Intel High End CPU (Core i7) 77 to 95 W
	Intel Top End CPU (Core i7-E) 130 to 150 W
	AMD Low End CPU (2 cores) 65 to 95 W
	AMD Mid End CPU (4 cores) 65 to 125 W
	AMD High End CPU (8 cores) 95 to 125 W	*/
	int cpuinfo()
	{
		FILE* in = fopen("/proc/cpuinfo", "r");

		char a[100], b[100];
		fgets(a, 100, in);
		sscanf(a, "processor\t: %d", id);

		for (int i = 0; i < 4; i++)
			fgets(a, 100, in);
		a[strlen(a) - 1] = '\0';
		strcpy(name, a + 13);//name

		for (int i = 0; i < 2; i++)
			fgets(a, 100, in);

		sscanf(a, "cpu MHz\t\t: %f", freq);
		fgets(a, 100, in);

		sscanf(a, "cache size\t: %d",cachesize);
		fclose(in);
		return 0;
	}

	void print()
	{
		printf
	}
};

