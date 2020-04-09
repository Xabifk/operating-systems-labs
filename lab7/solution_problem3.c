#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
	int a, b;


	int pread[2], cread[2];

	pipe(pread);
	pipe(cread);

	int pid = fork();

	if(pid == 0)
	{
		close(cread[1]);
		close(pread[0]);


		read(cread[0], &a, sizeof(int));
		read(cread[0], &b, sizeof(int));




		close(cread[0]);

		int sum = a + b;

		write(pread[1], &sum, sizeof(int));
		close(pread[1]);

		exit(0);
	}

	close(cread[0]);
	close(pread[1]);


	printf("%s", "Give me the numbers: ");

	scanf("%d %d", &a, &b);

	write(cread[1], &a, sizeof(int));
	write(cread[1], &b, sizeof(int));

	close(cread[1]);

	int sum = 0;

	wait(0);

	read(pread[0], &sum, sizeof(int));
	close(pread[0]);

	printf("The sum is %d\n", sum);

	return 0;
}
