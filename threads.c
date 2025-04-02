#include "philosophers.h"

void *philosophers_routine(void *arg)
{
    int id;

    id = *(int*)arg; // what kind of sorcery is this??
    printf("Philosopher nb. %d is thinking\n", id);
    return (NULL);
}

int creating_threads(t_val *input)
{
    int       i;
    pthread_t *philo;
    int       *id;

    i = 1;
    philo = malloc(sizeof(pthread_t) * (input->philo) + 1);
    id = malloc(sizeof(int) * (input->philo) + 1);
    while (i <= input->philo)
    {
        id[i] = i;
        pthread_create(&philo[i], NULL, philosophers_routine, &id[i]);
        i++;
    }
    i = 1;
    while (i <= input->philo)
    {
        pthread_join(philo[i], NULL);
        i++;
    }
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