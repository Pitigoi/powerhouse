#pragma once
#include "mem.h"
#include "cpu.h"
//#include "proc.h"

#define setpoint std::set<int>::iterator
class procman
{
private:
	procman();
	static procman* instance;
	static std::set<mem*> set;
	static cpu* cpu;
	procman(const procman& oth) = delete;
	procman& operator=(const procman& oth) = delete;
public:
	~procman();
	static procman* getInstance();
	static int size;
	proc* operator[](int index);
	static void updateList();
};