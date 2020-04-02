#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int sum = 0;
// memory is not shared between the parent and the child - the result won't be the total sum

int main()
{
	int v[50];
	int n;
	printf("n = ");
	scanf("%d", &n);

	for(int i = 0; i < n; i++)
	{
		scanf("%d", &v[i]);
	}

	int cid = fork();

	if(cid == 0)
	{
		for(int i = 0; i < n; i++)
		{
			if(v[i] % 2 == 0)
			{
				sum += v[i];
			}
		}
		printf("Sum till now %d\n", sum);
		exit(0);
	}

	wait(0);
	for(int i = 0; i < n; i++)
	{
		if(v[i] % 2 == 1)
		{
			sum += v[i];
		}
	}

	printf("Sumt at the end %d\n", sum);
	return 0;
}
