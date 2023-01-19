#define _CRT_SECURE_NO_WARNINGS
#include "procman.h"
#include "pthread.h"
#include "gpu.h"
#include "battery.h"


struct cons
{
	float gpu_total_cons;
	float cpu_total_cons;
	float mem_total_cons;
};
typedef struct cons cons_t;


static cons_t* cons = new cons_t();


void compute()
{
	std::set<proc*> list = procman::getInstance().getList();
	for(auto i=list.begin();i !=list.end();i++)
	{
		(*i)->setBatcons((*cons).cpu_total_cons,(*cons).gpu_total_cons, (*cons).mem_total_cons);
	}
	
}

void initialize_components() {

	Battery::getInstance().refresh();
	GPU::getInstance().setWatts();
	
	float bat_watts=Battery::getInstance().getCurrentEnergy();
	float gpuWatts=GPU::getInstance().getWatts();
	float cpuWatts=cpu::getInstance()->getWatts();
	mem* mem_instance=new mem();
	float memWatts=mem_instance->getAverage();

	(*cons).gpu_total_cons=gpuWatts*bat_watts/100;
	(*cons).cpu_total_cons=cpuWatts*bat_watts/100;
	(*cons).mem_total_cons=memWatts*bat_watts/100;
	
	
}

void init_procs_list()
{
	procman::getInstance().updateList((*cons).gpu_total_cons, (*cons).cpu_total_cons, (*cons).mem_total_cons);
}

void print_menu()
{
	printf("PID  \t CPU \t    GPU\t\tMEM\t TOTAL\t    BATTERY%\t\tNAME\n");
	printf("--------------------------------------------------------------------------------\n");
}


int main()
{
	
	while(1)
	{
		printf("Enter choice:\n");
		printf("1.Show all\n");
		printf("2.Search by pid\n");
		printf("3.Exit\n");
		
		int choice;
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				initialize_components();
				init_procs_list();
				compute();
				print_menu();
				procman::getInstance().print();
				break;
			
			case 2:

				printf("Enter pid:\n");
				int pid;
				scanf("%d", &pid);
				initialize_components();
				init_procs_list();
				compute();
				print_menu();
				procman::getInstance().print_by_pid(pid);
				break;

			case 3:
				exit(0);

		}
	}

	
	return 0;
}