#include <signal.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>


void term_signal()
{
	printf("No!\n");
}


int main() // we can kill it with kill -9 <pid>
{
	printf("I'm %d\n", getpid());
	signal(SIGTERM, term_signal);

	while(1)
	{
		sleep(1);
	}

	return 0;
}
