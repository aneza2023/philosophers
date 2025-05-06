
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
    free(forks[0]);
    free(forks);
    return (0);
}

int free_forks(t_philo **philosopher, pthread_mutex_t **forks, int id)
{
    int i;

    i = 0;
    while (i <= id)
    {
        free(philosopher[i]);
        i++;
    }
    free(philosopher);
    i = 0;
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
	if (forks[id + 1] == NULL)
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

// works but probably needs an upgrade, still delayed

// int	help_ftusleep()
// {
// 	struct timeval	current;
// 	int			start;

// 	gettimeofday(&current, NULL);
// 	start = (current.tv_sec * 1000000) + current.tv_usec;
// 	return (start);
// }

// int	ft_usleep(int microsec)
// {
// 	int	start;
// 	int	target_sleep;
// 	int	remains;

// 	start = help_ftusleep();
// 	while (help_ftusleep() - start < microsec)
// 	{
// 		remains = microsec - (help_ftusleep() - start);
// 		if (remains > 10000)
// 			usleep (remains / 2);
// 		else
// 		{
// 			while (remains > 0)
// 				remains = microsec - (help_ftusleep() - start);
// 		}
// 	}
// 	return (0);
// }
