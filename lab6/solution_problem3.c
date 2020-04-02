#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main()
{
	char command[51];
	printf("%s: ", "Your command please");
	fgets(command, 50, stdin);

	char *arguments[10];
	char *argument;
	int nr_arguments = 0;

	argument = strtok(command, " ");

	argument = strtok(NULL, " ");

	while(argument != NULL)
	{
		arguments[nr_arguments] = argument;
		nr_arguments += 1;
		argument = strtok(NULL, " ");
	}

	arguments[nr_arguments] = NULL;


	int pid = fork();
	if(pid == 0)
	{
		execvp(command, arguments);
		exit(0);
	}

	wait(0);

	return 0;
}
