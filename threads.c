#include "philosophers.h"

void *philosophers_routine(void *arg)
{
	t_philo *philosopher;

	philosopher = (t_philo *)arg;
	// printf ("philo %d here\n", philosopher->id);
	philosopher->nb_of_meals = 0; // putting values fce??
	philosopher->death = 0;
	return (NULL);
}
int	joining_threads(pthread_t *philo, t_philo **philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers[0]->input->philo)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (1);
}

int creating_threads(t_val *input)
{
	int       i;
	pthread_t *philo;
	t_philo   **philosopher;

	i = 0;
	philosopher = malloc(sizeof(t_philo) * (input->philo + 1));
	philo = malloc(sizeof(pthread_t) * (input->philo) + 1);
	if (philosopher == NULL || philo == NULL) // need to free, lines also issue
		return (1);
	while (i < input->philo)
	{
		philosopher[i] = malloc(sizeof(t_philo));
		memset(philosopher[i], 0, sizeof(t_philo));
		philosopher[i]->id = i + 1;
		philosopher[i]->input = input;
		// printf("philo %d\n", philosopher[i]->id);
		pthread_create(&philo[i], NULL, philosophers_routine, philosopher[i]);
		i++;
	}
	joining_threads(philo, philosopher);
	return (0);
}

// int         id;
// int         id2;
// pthread_t   philo1;
// pthread_t   philo2;

// id = 3;
// id2 = 8;
// pthread_create(&philo1, NULL, philosophers_routine, &id);
// pthread_create(&philo2, NULL, philosophers_routine, &id2);

// pthread_join(philo1, NULL);
// pthread_join(philo2, NULL);