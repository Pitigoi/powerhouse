#include <stdio.h>
#include <string.h>


typedef struct {
	int id;
	char name[100];
	float freq;
	int cachesize;
} cpu;

cpu cpuinfo()
{
	/*Intel Low End CPU (Core i3) 55 to 73 W
	Intel Mid End CPU (Core i5) 73 to 95 W
	Intel High End CPU (Core i7) 77 to 95 W
	Intel Top End CPU (Core i7-E) 130 to 150 W
	AMD Low End CPU (2 cores) 65 to 95 W
	AMD Mid End CPU (4 cores) 65 to 125 W
	AMD High End CPU (8 cores) 95 to 125 W	*/
  	FILE* in =fopen("/proc/cpuinfo","r");
  	
	cpu out;
	
	char a[100],b[100];
	fgets(a,100,in);
	sscanf(a,"processor\t: %d",&out.id);

	for(int i=0;i<4;i++)
    	fgets(a,100,in);
  	a[strlen(a)-1]='\0';
	strcpy(out.name,a+13);

  	for(int i=0;i<2;i++)
    	fgets(a,100,in);
  	
	sscanf(a,"cpu MHz\t\t: %f",&out.freq);
    fgets(a,100,in);
  	
	sscanf(a,"cache size\t: %d",&out.cachesize);
  	fclose(in);
	return out;
}


void mboardinfo(){
	/*Regular Motherboard 25 to 40 W
	High End Motherboard 45 to 80 W

	Factors that affect motherboard power consumption: number of power phases, type of voltage regulator, integrated chipsets and modules (e.g. on-board sound, on-board Wi-Fi, add-on USB connectors, add-on SATA connectors etc.) and BIOS power saving features.
	*/
	printf("");
}

typedef struct {
	int total;
	char name[100];
	float freq;
	int cachesize;
	int count;
} mem;

mem meminfo()
{
	/*DDR1 RAM (2.5 Volts) 4 to 5.5 W
	DDR2 RAM (1.8 Volts) 3 to 4.5 W
	DDR3 RAM (1.5 Volts) 2 to 3 W

	A higher clock speed will also lead to higher power consumption (e.g. DDR3 RAM running at 2,133 MHz will use more power than DDR3 RAM at 1,600 MHz).

	Interestingly the amount of RAM has little or no effect on power consumption of PC components. A stick of 4 GB DDR3 RAM will draw about the same amount of power as a stick of 8 GB DDR3 RAM (assuming that they have the same clock speed).
	*/
	mem out;

  	FILE* in =fopen("/proc/meminfo","r");
  	char a[100],b[100];
	fgets(a,100,in);
	sscanf(a,"MemTotal:\t\t%d",&out.total);
  	fclose(in);
	return out;
}

#include <unistd.h>
#include <stdlib.h>

mem meminfo2()
{
	/*DDR1 RAM (2.5 Volts) 4 to 5.5 W
	DDR2 RAM (1.8 Volts) 3 to 4.5 W
	DDR3 RAM (1.5 Volts) 2 to 3 W

	A higher clock speed will also lead to higher power consumption (e.g. DDR3 RAM running at 2,133 MHz will use more power than DDR3 RAM at 1,600 MHz).

	Interestingly the amount of RAM has little or no effect on power consumption of PC components. A stick of 4 GB DDR3 RAM will draw about the same amount of power as a stick of 8 GB DDR3 RAM (assuming that they have the same clock speed).
	*/
	mem out;

	int fd[2];
	if(	pipe(fd)<0)
		printf("error : pipe\n");
	
	if(0==0)
	{
		int pid = fork();
		switch (pid) {
			case -1: /* fork failed */
				printf("error : pipe\n");
				exit(EXIT_FAILURE);
			case 0: /* child process */
				close(fd[0]);
				dup2(fd[1],1);

				execl("/bin/sh", "sh", "-c", "dmidecode --type memory", (char *) NULL);
			default: /* parent process */
				close(fd[1]);

				char readingbuf[2]="a";
				char childout[512]="";
				while(read(fd[0],readingbuf,1)>0)
				{
					strcat(childout,readingbuf);
					//write(1,readingbuf,1);
				}
				close(fd[0]);
				int status;
				wait(pid,&status);


				printf("Created process with pid %d\n%s\n", pid,childout);
		}
		//pid = wait(&status);
	}
	return out;
}

void function_template(const char* command)
{
	

	int fd[2];
	if(	pipe(fd)<0)
		printf("error : pipe\n");
	
	int pid = fork();
	switch (pid) {	
		case -1: 
			printf("error : pipe\n");
			exit(EXIT_FAILURE);
		case 0: 
			close(fd[0]);
			dup2(fd[1],1);
			//execl("/bin/sh", "sh", "-c", "echo \"proba\"", (char *) NULL);
			execl("/bin/sh", "sh", "-c", command, (char *) NULL);
		default: 
			close(fd[1]);

			char readingbuf[2]="a";
			char childout[512]="";
			while(read(fd[0],readingbuf,1)>0)
			{
				strcat(childout,readingbuf);
			}
			close(fd[0]);
			int status;
			wait(pid,&status);
			printf("Created process with pid %d\n%s\n", pid,childout);
	}
	
}

void pipe_to_file(const char* command,const char* path)
{
	int pid = fork();
	switch (pid) {
		case -1:
			printf("error : fork\n");
			exit(EXIT_FAILURE);
		case 0:
			int out = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
			dup2(out, 1);
			//execl("/bin/sh", "sh", "-c", "echo \"proba\"", (char *) NULL);
			execl("/bin/sh", "sh", "-c", command, (char*)NULL);
		default:
			int status;
			wait(pid, &status);
			printf("Proces cu out redirectat la %s/n", path);
	}
}

void main()
{
	cpu  a = cpuinfo();
	//printf("%d %s\n%f %d\n",a.id,a.name,a.freq,a.cachesize);
	mem b = meminfo2();
	//printf("%d kbs\n",b.total);
}