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
	//int consum;
public:
	/*DDR1 RAM (2.5 Volts) 4 to 5.5 W
	DDR2 RAM (1.8 Volts) 3 to 4.5 W
	DDR3 RAM (1.5 Volts) 2 to 3 W

	A higher clock speed will also lead to higher power consumption (e.g. DDR3 RAM running at 2,133 MHz will use more power than DDR3 RAM at 1,600 MHz).

	Interestingly the amount of RAM has little or no effect on power consumption of PC components. A stick of 4 GB DDR3 RAM will draw about the same amount of power as a stick of 8 GB DDR3 RAM (assuming that they have the same clock speed).
	*/
	
	static int setTotal();
	
	static int getHandles();

	int fillByHandle(char handle[5]);
};

