#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
class mem
{
protected:
	int total;
	char name[100];
	float freq;
	int cachesize;
	int count;
	//int consum;
public:
	/*DDR1 RAM (2.5 Volts) 4 to 5.5 W
	DDR2 RAM (1.8 Volts) 3 to 4.5 W
	DDR3 RAM (1.5 Volts) 2 to 3 W

	A higher clock speed will also lead to higher power consumption (e.g. DDR3 RAM running at 2,133 MHz will use more power than DDR3 RAM at 1,600 MHz).

	Interestingly the amount of RAM has little or no effect on power consumption of PC components. A stick of 4 GB DDR3 RAM will draw about the same amount of power as a stick of 8 GB DDR3 RAM (assuming that they have the same clock speed).
	*/
	mem()
	{
		lungime = w;
		latime = l;
		grosime = h;
	}

	int total()
	{
		FILE* in = fopen("/proc/meminfo", "r");
		char a[100], b[100];
		fgets(a, 100, in);
		sscanf(a, "MemTotal:\t\t%d", total);
		fclose(in);
	}

	int suprafataTotala()
	{
		mem out;

		int fd[2];
		if (pipe(fd) < 0)
			printf("error : pipe\n");

		if (0 == 0)
		{
			int pid = fork();
			switch (pid) {
			case -1: /* fork failed */
				printf("error : fork\n");
				exit(EXIT_FAILURE);
			case 0: /* child process */
				close(fd[0]);
				dup2(fd[1], 1);

				execl("/bin/sh", "sh", "-c", "dmidecode -t 17", (char*)NULL);
				//"dmidecode -t 17 | grep -o \"Handle 0x....\""				
			}

			close(fd[1]);

			char readingbuf[2] = "a";
			char childout[512] = "";
			while (read(fd[0], readingbuf, 1) > 0)
			{
				strcat(childout, readingbuf);
			}
			close(fd[0]);
			int status;
			wait(pid, &status);
			
			int cnt=0;
			for (char* p i = strchr(readingbuf, 'x'); p != null; p = strchr(p + 1, 'x'))
				cnt++;
			char handles[cnt][5];
			
			char* p=strchr(readingbuf,'x')
			for(int i=0;i<cnt;i++){
				for(int j=0;j<4;j++)
					handles[cnt][j]=p[j+1];

				handles[cnt][j] = 0;
				p=strchr(p + 1, 'x');
			}
			char command[] = "dmidecode -H 0x001B";
			for (int i = 0; i < cnt; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					command[j+15]=handles[]
				}
				pid = fork();
				switch (pid) {
				case -1: /* fork failed */
					printf("error : fork\n");
					exit(EXIT_FAILURE);
				case 0: /* child process */
					close(fd[0]);
					dup2(fd[1], 1);
					printf("%s\n", command);
					execl("/bin/sh", "sh", "-c", command, (char*)NULL);		
				}
			}
			printf("Created process with pid %d\n%s\n", pid, childout);
		}
		return out;
	}
};

