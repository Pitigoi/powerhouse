#pragma once
#include "mem.h"
#include "cpu.h"
#include "gpu.h"
#include "battery.h"
#include <set>
#include <sys/wait.h>

class hwman
{
private:
	hwman();
	static hwman* instance;
	static cpu* CPU;
	static GPU* gpu;
	static std::set<mem*> mems;
	static Battery bat;
	hwman(const hwman& oth) = delete;
	int getHandles();
	hwman& operator=(const hwman& oth) = delete;
public:
	~hwman();
	static hwman& getInstance();
	static int size;//de mem
	mem* memory(int index);
	static float gpucons(int pid);
};