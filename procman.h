#pragma once
#include "proc.h"

#define setpoint std::set<int>::iterator
class procman
{
private:
	procman();
	static procman* instance;
	static proc* table[];
	static std::set<proc*> set;
	procman(const procman& oth) = delete;
	procman& operator=(const procman& oth) = delete;
public:
	~procman();
	static procman* getInstance();
	static int size;
	proc* operator[](int index);
	static void updateList();
};