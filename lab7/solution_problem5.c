#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>




int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		exit(1);
	}

	int pipe1[2];

	pipe(pipe1);

	int pid = fork();

	if(pid == 0)
	{
		close(pipe1[0]);

		dup2(pipe1[1], 1);

		execl("/bin/grep", "/bin/grep/", argv[1], argv[2], NULL);
		exit(1);
	}


	close(pipe1[1]);

	wait(0);

	char text[400];
	char *now = text - 1;

	do
	{
		now += 1;
		read(pipe1[0], now, 1);
	}
	while(*now != '\0');
	close(pipe1[0]);


	char line[200];

	now = line - 1;


	for(int i = 0; i <= strlen(text); i++)
	{
		do
		{
			now += 1;
			*now = text[i];
			i++;
		}
		while(*now != '\n' && *now != '\0');
		*now = '\0';

		if(strlen(line) % 3 == 0)
		{
			printf("%s\n", line);
		}

		now = line - 1;
		i--;
	}

	return 0;
}

