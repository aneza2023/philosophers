#include "philosophers.h"

void    free_finish(t_philo **phil, pthread_t *philos, pthread_mutex_t **forks, t_val *input)
{
    int i;

    i = 0;
    while (forks[i] != NULL)
    {
        free(forks[i]);
        i++;
    }
    free(forks);
    free(philos);
    free(phil);
}
