
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

int free_forks(t_philo **philosopher, pthread_t *philo,
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
    i = 1;
    while (i < id)
    {
        free(forks[i]);
        i++;
    }
    free(forks);
    return (0);
}

// int	free_philo_values()
// {

// }