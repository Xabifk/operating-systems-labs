#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


void fork_if_even(int pid)
{
	if(pid % 2 == 0)
	{
		int id = fork();
		if(id == 0)
		{
			printf("My pid is %d\n", getpid());
			fork_if_even(getpid());
			exit(0);
		}

		wait(0);
		printf("%d is dead\n", id);
	}

}



int main()
{

	fork_if_even(0);
	return 0;
}



