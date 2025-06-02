#include "philosophers.h"

void    free_finish(t_philo **phil, pthread_t *philos, pthread_mutex_t **forks, int id)
{
    int i;

    i = 0;
    while (i <= id + 1)
    {
        free(forks[i]);
        i++;
    }
    i = 0;
    while (i <= id)
    {
        if (i == 0)
        {
            pthread_mutex_destroy(phil[i]->lock_time);
            free(phil[i]->lock_time);
        }
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
    {
        pthread_mutex_destroy(phil->lock_somedeath);
        free(phil->lock_somedeath);
    }
    if (phil->lock_last_meal != NULL)
    {
        pthread_mutex_destroy(phil->lock_last_meal);
        free(phil->lock_last_meal);
    }
    if (phil->lock_nb_meals != NULL)
    {
        pthread_mutex_destroy(phil->lock_nb_meals);
        free(phil->lock_nb_meals);
    }
}
