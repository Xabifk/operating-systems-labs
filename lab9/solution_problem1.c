#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

int number_of_vowels = 0;
int number_of_digits = 0;

pthread_mutex_t vowels_mutex;
pthread_mutex_t digits_mutex;

void* check_string(void* argument)
{
	char* string = (char *)argument;
	int len = strlen(string);

	for(int i = 0; i < len; i++)
	{
		if(strchr("aeiou", string[i]) != NULL)
		{
			pthread_mutex_lock(&vowels_mutex);
			number_of_vowels += 1;
			pthread_mutex_unlock(&vowels_mutex);
		}

		if(strchr("1234567890", string[i]) != NULL)
		{
			pthread_mutex_lock(&digits_mutex);
			number_of_digits += 1;
			pthread_mutex_unlock(&digits_mutex);
		}
	}

	return NULL;
}

int main()
{
	pthread_t threads[5];
	int error;
	char *strings[] = {"12aa", "ffa", "00i", "eeee", "aeiou1234567890"};

	pthread_mutex_init(&vowels_mutex, NULL);
	pthread_mutex_init(&digits_mutex, NULL);

	for(int i = 0; i < 5; i++)
	{

		error = pthread_create(&threads[i], NULL, check_string, (void *)strings[i]);
		if(error != 0)
		{
			printf("%s\n", "Error");
			exit(1);
		}

	}

	for(int i = 0; i < 5; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("Number of vowels: %d\n" , number_of_vowels);
	printf("Number of digits: %d\n" , number_of_digits);

	pthread_mutex_destroy(&vowels_mutex);
	pthread_mutex_destroy(&digits_mutex);

	return 0;
}
