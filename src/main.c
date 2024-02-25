#include "philo.h"

pthread_mutex_t mutex;

void *roll_dice()
{
	pthread_mutex_lock(&mutex);
	int value = (rand() % 6) + 1;
	int	*res = malloc(sizeof(int));
	*res = value;
	pthread_mutex_unlock(&mutex);
	return ((void*)res);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	srand(time(NULL));
	int			*res;
	pthread_t	th[4];

	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(th + i, NULL, &roll_dice, NULL) != 0)
			return (1);
	}
	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], (void**)&res) != 0)
			return (2);
		printf("Result = %d\n", *res);
	}
	pthread_mutex_destroy(&mutex);

	return (0);
}
