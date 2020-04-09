#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


int main()
{
	int a, b;
	char path[] = "/tmp/pb6";
	mkfifo(path, 0666);
	FILE *handle;

	int pid = fork();

	if(pid == 0)
	{
		handle = fopen(path, "rb");
		fread(&a, 1, sizeof(int), handle);
		fread(&b, 1, sizeof(int), handle);

		fclose(handle);
		unlink(path);

		int sum = a + b;

		handle = fopen(path, "wb");
		fwrite(&sum, 1, sizeof(int), handle);


		fclose(handle);

		exit(0);
	}


	handle = fopen(path, "wb");

	printf("%s", "Give me the numbers: ");

	scanf("%d %d", &a, &b);

	fwrite(&a, 1, sizeof(int), handle);
	fwrite(&b, 1, sizeof(int), handle);

	fclose(handle);
	unlink(path);

	int sum = 0;

	wait(0);

	handle = fopen(path, "rb");
	fread(&sum, 1, sizeof(int), handle);

	printf("The sum is %d\n", sum);

	fclose(handle);

	unlink(path);

	return 0;
}
