#pragma once
#include "mem.h"
#include "cpu.h"
#include <set>
//#include "battery.h"
//#include "proc.h"

#define setpoint std::set<int>::iterator
class hwman
{
private:
	hwman();
	static hwman* instance;
	static cpu* cpu;
	static std::set<mem*> mems;
	hwman(const hwman& oth) = delete;
	int getHandles();
	hwman& operator=(const hwman& oth) = delete;
public:
	~hwman();
	static hwman* getInstance();
	static int size;
	mem* memory(int index);
};