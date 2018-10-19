#include <sys/cdefs.h>

#include <sys/mman.h>
#include <sys/ioctl.h>
#include <err.h> 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define _PATH_DEV_MAPPER "/dev/chall2"
#define INPUT "C@C@@@C@@@CC@C@C@@@CCC@@@@CC@@C@CCCC@C@@@@@@CCC@C"
#define KREVDEC _IO('K', 3)
#define KREVFLAG _IO('K', 2)
#define KREVINC _IO('K', 1)

#define BUFFER_LEN 100

int main(int argc, char **argv)
{
	int devfd;
	char *map = NULL;
	char *buf;

	buf = malloc(50);

	if ((devfd = open(_PATH_DEV_MAPPER, O_RDWR)) == -1)
		err(EXIT_FAILURE, "Cannot open %s", _PATH_DEV_MAPPER);
	
	map=mmap(0, BUFFER_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, devfd, 0);
	if(map == MAP_FAILED)
		err(EXIT_FAILURE, "Mapping failed"); 

	snprintf(map, BUFFER_LEN, INPUT);
	write(devfd,"!",2);
	for(int i = 0; i < 16; i++)
                if(ioctl(devfd, KREVINC)== -1)
		    printf("error");
	ioctl(devfd, KREVFLAG);
	read(devfd, buf, 100);
	printf("%s", buf);
	if (close(devfd) == -1)
		err(EXIT_FAILURE, "Cannot close %s", _PATH_DEV_MAPPER);

	return EXIT_SUCCESS;
}
