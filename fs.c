#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// struct meminf{

// };

// char* mem(){
// return NULL;
// }


int so_fopen(const char* pathname, const char* mode) {
	int fd, flags;
	mode_t mode2 = S_IRWXU | S_IRWXG | S_IRWXO;
	if (strcmp(mode, "r") == 0)
	{
		flags = O_RDONLY;

	}
	else if (strcmp(mode, "r+") == 0)
	{
		flags = O_RDWR | O_CREAT;
	}
	else if (strcmp(mode, "w") == 0)
	{
		flags = O_WRONLY | O_CREAT;

	}
	else if (strcmp(mode, "w+") == 0)
	{
		flags = O_RDWR | O_CREAT;

	}
	else if (strcmp(mode, "a") == 0)
	{
		flags = O_WRONLY | O_CREAT;

	}
	else if (strcmp(mode, "a+") == 0)
	{
		flags = O_RDWR | O_CREAT;

	}
	else return -1;
	if (flags & O_CREAT)
		fd = open(pathname, flags, mode2);
	else fd = open(pathname, flags);

	return fd;
	//r r+ w w+ a a+
	//O_RDONLY, O_WRONLY, or O_RDWR
}

int so_fclose(int stream) {
	return close((stream));
}

int so_fgetc(int stream) {
	char e;
	int bytesread = read(stream, &e, 1);
	if (bytesread == 1)
		return -1;
	return (int)e;
}

char* so_getline(int fd){
    char *buf;
//    buf=(char*) malloc(200);
    char a=(char) so_fgetc(fd);
//    int size=0;
//     do{
//         buf[size]=a;
//         size++;
//         a=(char) so_fgetc(fd);
//     }while(a!='\n');
//     buf[size-1]=0;
    return buf;
}

char* so_strchr(char* arr,char chr){
    int n=strlen(arr);
    for(int i=0;i<n;i++)
    {
        if(arr[i]==chr)
            return arr+i;
    }
    return NULL;
}

void so_strcpy(char* dst,char* src){
    for(int i=0;i<strlen(src);i++)
	{
		dst[i]=src[i];
	}
}

size_t so_fwrite(const void* ptr, size_t size, size_t nmemb, int stream) {
	int byteswritten = 0;
	for (int count = 0; count < nmemb; count++)
		byteswritten += pwrite(stream, ptr, size, size * count);

	return byteswritten;
}

typedef struct {
    int id;//line 0
    char* name;//line 5
    float mhz;//ln 7
    int cache;//ln8
} cpuinf;

cpuinf cpu(){
    int fd=so_fopen("/proc/cpuinfo","r");
    
    cpuinf out;
	//char* a=so_getline(fd);
	// free(a);
	// a=so_getline(fd);
	// free(a);
	// a=so_getline(fd);
	// free(a);
	// a=so_getline(fd);
	// free(a);
	// a=so_getline(fd);
	out.name=malloc(200);
	//so_strcpy(out.name,a);
	// free(a);
	out.name[0]=so_fgetc(fd);
	out.name[1]='\0';


    so_fclose(fd);
}

int main()
{
    cpuinf a = cpu();
	//so_fwrite(&a.id,1,sizeof(int),1);
	//so_fwrite(&a.name,1,sizeof(int),1);
	free(a.name);
    return 0;
}B��)��牴證⑄䐈