
#include "philosophers.h"

int free_philosopher(t_philo **philosopher, pthread_t *philo,
    pthread_mutex_t **forks, int id)
{
    int i;

    i = 0;
    while (i < id)
    {
        free(philosopher[i]);
        i++;
    }
    free(philosopher);
    free(philo);
    free(forks);
    return (0);
}

int free_forks(t_philo **philosopher, pthread_mutex_t **forks, int id)
{
    int i;

    i = 0;
    while (i < id)
    {
        free(philosopher[i]);
        i++;
    }
    free(philosopher);
    i = 1;
    while (i <= id)
    {
        free(forks[i]);
        i++;
    }
    free(forks);
    return (0);
}

int	adding_forks(t_philo **philosopher, pthread_mutex_t **forks, int id)
{
	forks[id + 1] = malloc(sizeof(pthread_mutex_t));
	if (forks == NULL)
	{
		free_forks(philosopher, forks, id);
		return (1);
	}
	pthread_mutex_init(forks[id + 1], NULL);
	philosopher[id]->lfork = forks[id];
	philosopher[id]->id = id + 1;
	if (id != philosopher[id]->input->philo - 1)
		philosopher[id]->rfork = forks[id + 1];
	if (id == philosopher[id]->input->philo - 1)
		philosopher[id]->rfork = forks[0];
	return (0);
}


// int	free_philo_values()
// {

// }