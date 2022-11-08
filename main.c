#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

char *plus(int fd)
{
    static char	b[20];
	static int	i = 0;

	if (b[i] != '\0')
		read(fd, b, 19);
	b[19] == '\0';
	while(b[i] && b[i] != ' ')
	{
		printf("%c", b[i]);
		i++;
	}
	printf("\n");
	return (b);
}

int main()
{
    int fd;

	fd = open("ejemplo1.txt", O_RDONLY);
	plus(fd);
    /*printf("%s\n", plus(fd));*/
	close(fd);
    return (0);
}
