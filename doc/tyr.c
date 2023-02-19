#include <fcntl.h>
#include <stdio.h>
#include  <unistd.h>
int main()
{
	int fd = open("../../here_documents", O_RDWR, 0777);
	write(fd, "hello hello hello how low", 25);
	printf("%d", fd);
}