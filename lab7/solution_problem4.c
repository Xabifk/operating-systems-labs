#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int pipe1[2], pipe2[2];
	char word[90];

	pipe(pipe1);
	pipe(pipe2);

	int pid = fork();

	if(pid == 0)
	{
		// child 1
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[1]);

		int total_len = 0;
		int len;

		while(1)
		{
			read(pipe2[0], &len, sizeof(int));
			read(pipe2[0], word, len);

			len = strlen(word);
			if(len == 0)
			{
				break;
			}

			total_len += len;
		}
		close(pipe2[0]);

		printf("Child 1 %d\n", total_len);

		exit(0);
	}

	pid = fork();

	if(pid == 0)
	{
		//child 2
		close(pipe2[0]);
		close(pipe2[1]);
		close(pipe1[1]);

		int total_len = 0;
		int len;

		while(1)
		{
			read(pipe1[0], &len, sizeof(int));
			read(pipe1[0], word, len);

			len = strlen(word);
			if(len == 0)
			{
				break;
			}

			total_len += len;
		}
		close(pipe1[0]);

		printf("Child 2 %d\n", total_len);

		exit(0);
	}

	close(pipe1[0]);
	close(pipe2[0]);
	int len;

	while(1)
	{
                fgets(word, 90, stdin);

		if(*word == '\n')
		{
			len = 1;
			*word = '\0';
			write(pipe1[1], &len, sizeof(int));
			write(pipe1[1], word, len);
			write(pipe2[1], &len, sizeof(int));
			write(pipe2[1], word, len);

			close(pipe1[1]);
			close(pipe2[1]);
			break;
		}
		len = strlen(word);
		word[len - 1] = '\0';

		len = strlen(word);
		len += 1;

		if(strstr(word, "oa") != NULL)
		{
			write(pipe1[1], &len, sizeof(int));
			write(pipe1[1], word, len);
		}
		else
		{
			write(pipe2[1], &len, sizeof(int));
			write(pipe2[1], word, len);
		}

	}

	wait(0);
	wait(0);

	return 0;
}

