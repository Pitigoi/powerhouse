#pragma once
#include "proc.h"
#include <set>
#define procpoint std::set<proc*>::iterator
class procman
{
private:
	procman();
	static procman* instance;
	static std::set<proc*> set;
	procman(const procman& oth) = delete;
	procman& operator=(const procman& oth) = delete;
public:
	~procman();
	static procman& getInstance();
	static int size;
	proc* operator[](int index);
	static void print();

	
	static void updateList(float cpu, float gpu, float mem);
	//Ioana
	std::set<proc*> getList();
	proc* search_list(int pid);
	void print_by_pid(int pid);
	//
};