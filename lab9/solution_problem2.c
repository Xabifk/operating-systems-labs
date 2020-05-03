#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int number_of_div_5 = 0;
int number_of_div_2 = 0;

pthread_mutex_t div_5_mutex;
pthread_mutex_t div_2_mutex;

void* check_number(void *argument)
{
	char *string = (char*) argument;

	int number = atoi(string);

	if(number % 5 == 0)
	{
		pthread_mutex_lock(&div_5_mutex);
		number_of_div_5 += 1;
		pthread_mutex_unlock(&div_5_mutex);
	}

	if(number % 2 == 0)
	{
		pthread_mutex_lock(&div_2_mutex);
		number_of_div_2 += 1;
		pthread_mutex_unlock(&div_2_mutex);
	}

	return NULL;
}

int main(int argc, char** argv)
{
	pthread_mutex_init(&div_5_mutex, NULL);
	pthread_mutex_init(&div_2_mutex, NULL);

	pthread_t threads[argc];
	int error = 0;

	for(int i = 1; i < argc; i++)
	{
		error = pthread_create(&threads[i], NULL, check_number, (void *)argv[i]);
		if(error != 0)
		{
			printf("%s\n", "Error");
			exit(1);
		}
	}

	for(int i = 1; i < argc; i++)
	{
		pthread_join(threads[i], NULL);
	}


	printf("Number of divs for 5: %d\n", number_of_div_5);
	printf("Number of divs for 2: %d\n", number_of_div_2);



	pthread_mutex_destroy(&div_5_mutex);
	pthread_mutex_destroy(&div_2_mutex);

	return 0;
}
