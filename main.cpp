#define _CRT_SECURE_NO_WARNINGS
#include "procman.h"
#include "hwman.h"

void main()
{
	procman* pm = procman::getInstance();
	hwman* hm = hwman::getInstance();
}