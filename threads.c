#include "philosophers.h"

void *philosophers_routine(void *arg)
{
    int id;

    id = *(int*)arg; // what kind of sorcery is this??
    printf("Philosopher nb. %d is thinking", id);
    return (NULL);
}

int creating_threads(t_val *input)
{
    int      id;
    t_thread philo1;

    id = 3;
    philo1 = malloc(sizeof(t_thread));
    pthread_create(&philo1, NULL, philosophers_routine, &id);

    return (0);
}