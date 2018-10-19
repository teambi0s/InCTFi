#include <sys/cdefs.h>

#include <string.h>
#include <err.h> 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define _PATH_DEV_MAPPER "/dev/chall1"
#define INPUT "W3lC0Me"

int main(int argc, char **argv)
{
	int devfd;
	char *buf;

	buf = malloc(50);

	if ((devfd = open(_PATH_DEV_MAPPER, O_RDWR)) == -1)
		err(EXIT_FAILURE, "Cannot open %s", _PATH_DEV_MAPPER);

	/* Your code here */
	write(devfd,INPUT, strlen(INPUT) + 1);
	read(devfd, buf, 100);
	printf("%s", buf);
	if (close(devfd) == -1)
		err(EXIT_FAILURE, "Cannot close %s", _PATH_DEV_MAPPER);

	return EXIT_SUCCESS;
}
