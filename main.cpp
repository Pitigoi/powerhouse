#define _CRT_SECURE_NO_WARNINGS
#include "procman.h"

int main()
{
	int a=12;
	procman::getInstance().updateList();
	//procman::print();

	return 0;
}