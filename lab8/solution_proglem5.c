#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


typedef struct
{
	int start;
	int end;
	int return_value;
} Interval;

int current_number;
int number_of_primes;

pthread_mutex_t mutex_primes = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_number = PTHREAD_MUTEX_INITIALIZER;

int is_prime(int number)
{
	if(number == 2)
	{
		return 1;
	}

	if(number % 2 == 0)
	{
		return 0;
	}


	for(int i = 3; i * i < number; i++)
	{
		if(number % i == 0)
		{
			return 0;
		}
	}

	return 1;
}

void* check_interval(void *void_interval)
{
	Interval *interval = (Interval*)void_interval;
	int start = interval->start;
	int end = interval->end;

	int total = 0;
	for(int i = start; i < end; i++)
	{
		if(is_prime(i) == 1)
		{
			total += 1;
		}
	}

	interval->return_value = total;
	return NULL;
}


void* check_current_number()
{
	while(current_number <= 200000000)
	{
		if(is_prime(current_number) == 1)
		{
			number_of_primes += 1;
		}
		current_number += 1;
	}

	return NULL;

}

void* check_current_number_mutex()
{
	int aux;
	while(current_number <= 200000000)
	{
		pthread_mutex_lock(&mutex_number);
		aux = current_number;
		current_number += 1;
		pthread_mutex_unlock(&mutex_number);

		if(is_prime(aux) == 1)
		{
			pthread_mutex_lock(&mutex_primes);
			number_of_primes += 1;
			pthread_mutex_unlock(&mutex_primes);
		}
	}

	return NULL;

}





void check_n_threads(int n)
{
	pthread_t threads[n];
	Interval intervals[n];
	int return_value;

	for(int i = 0; i < n; i++)
	{
		intervals[i].start = 200000000 * i / n + 1;
		intervals[i].end = 200000000 * (i + 1) / n;
		return_value = pthread_create(&threads[i], NULL, check_interval, &intervals[i]);

		if(return_value)
		{
			printf("Error\n");
			exit(1);
		}


	}

	int total = 0;

	for(int i = 0; i < n; i++)
	{
		pthread_join(threads[i], NULL);
		total += intervals[i].return_value;
	}

	number_of_primes = total;
}

void check_n_threads_no_sincro(int n)
{

	pthread_t threads[n];
	int return_value;

	for(int i = 0; i < n; i++)
	{
		return_value = pthread_create(&threads[i], NULL, check_current_number, NULL);

		if(return_value)
		{
			printf("Error\n");
			exit(1);
		}


	}

	for(int i = 0; i < n; i++)
	{
		pthread_join(threads[i], NULL);
	}
}


void check_n_threads_mutex(int n)
{

	pthread_t threads[n];
	int return_value;

	for(int i = 0; i < n; i++)
	{
		return_value = pthread_create(&threads[i], NULL, check_current_number_mutex, NULL);

		if(return_value)
		{
			printf("Error\n");
			exit(1);
		}


	}

	for(int i = 0; i < n; i++)
	{
		pthread_join(threads[i], NULL);
	}
}




int main()
{
	time_t start, end;

	/*
	for(int i = 1; i <= 8; i *= 2)
	{
		current_number = 1;

		number_of_primes = 0;
		start = time(NULL);

		printf("%d threads\n", i);

		check_n_threads(i);

		end = time(NULL);

		printf("%d threads takes %.0f and found %d primes\n\n", i, difftime(end, start), number_of_primes);
	}


	for(int i = 4; i <= 8; i *= 2)
	{
		current_number = 1;

		number_of_primes = 0;
		start = time(NULL);

		printf("%d threads\n", i);

		check_n_threads_no_sincro(i);

		end = time(NULL);

		printf("%d threads takes %.0f and found %d primes\n\n", i, difftime(end, start), number_of_primes);
	}
	*/



	for(int i = 4; i <= 8; i *= 2)
	{
		current_number = 1;

		number_of_primes = 0;
		start = time(NULL);

		printf("%d threads\n", i);

		check_n_threads_mutex(i);

		end = time(NULL);

		printf("%d threads takes %.0f and found %d primes\n\n", i, difftime(end, start), number_of_primes);
	}



	return 0;
}
