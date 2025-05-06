#include "philosophers.h"

void    free_finish(t_philo **phil, pthread_t *philos, pthread_mutex_t **forks)
{
    int i;

    i = 0;
    forks[phil[0]->philo_nb + 1] = NULL;
    phil[phil[0]->philo_nb] = NULL;
    while (forks[i] != NULL)
    {
        free(forks[i]);
        i++;
    }
    i = 0;
    while (phil[i] != NULL)
    {
        free_mutaxes(phil[i]);
        free(phil[i]);
        i++;
    }
    free(forks);
    free(philos);
    free(phil);
}

void    free_mutaxes(t_philo *phil)
{
    if (phil->lock_somedeath != NULL)
        free(phil->lock_somedeath);
    if (phil->lock_last_meal != NULL)
        free(phil->lock_last_meal);
    if (phil->lock_nb_meals != NULL)
        free(phil->lock_nb_meals);
}
