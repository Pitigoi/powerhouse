#pragma once
#include <stdio.h>
#include <string.h>
class cpu 
{
private:
	cpu();
	static cpu* instance;

	cpu(const cpu& oth) = delete;
	cpu& operator=(const cpu& oth) = delete;
protected:
	int id;
	char name[100];
	float freq;
	int cachesize;
	//int consum;
public:
	~cpu();
	static cpu* getInstance();

	/*Intel Low End CPU (Core i3) 55 to 73 W
	Intel Mid End CPU (Core i5) 73 to 95 W
	Intel High End CPU (Core i7) 77 to 95 W
	Intel Top End CPU (Core i7-E) 130 to 150 W
	AMD Low End CPU (2 cores) 65 to 95 W
	AMD Mid End CPU (4 cores) 65 to 125 W
	AMD High End CPU (8 cores) 95 to 125 W	*/

	int cpuinfo();

	void print()
	{
		printf
	}
};

