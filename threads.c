/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:54:51 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/17 15:19:42 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

suseconds_t	t_stamp(struct timeval original_time)
{
	struct timeval	current_time;
	suseconds_t		result;
	time_t			betweenres;

	gettimeofday(&current_time, NULL);
	betweenres = (current_time.tv_sec - original_time.tv_sec) * 1000;
	result = (current_time.tv_usec - original_time.tv_usec) / 1000;
	result = betweenres + result;
	return (result);
}

void	*philosophers_routine(void *arg)
{
	t_philo		*philosopher;

	philosopher = (t_philo *)arg;
	start_with_even(philosopher);
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

int	creating_threads_cont(t_philo **philosopher, pthread_t *philo,
	pthread_mutex_t **forks, t_val *input)
{
	int	i;

	i = 0;
	forks[i] = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(forks[i], NULL);
	while (i < input->philo)
	{
		philosopher[i] = malloc(sizeof(t_philo));  //free needed, allocation failed
		memset(philosopher[i], 0, sizeof(t_philo));
		philosopher[i]->id = i + 1;
		philosopher[i]->input = input;
		forks[i + 1] = malloc(sizeof(pthread_mutex_t)); //free needed if allocation failed
		pthread_mutex_init(forks[i + 1], NULL);
		philosopher[i]->lfork = forks[i];
		if (i != input->philo - 1)
			philosopher[i]->rfork = forks[i + 1];
		if (i == input->philo - 1)
			philosopher[i]->rfork = forks[0];
		putting_val_phil(philosopher[i]);
		pthread_create(&philo[i], NULL, philosophers_routine, philosopher[i]);
		i++;
	}
	creating_observer(philosopher, philo);
	return (0);
}

int	creating_threads(t_val *input)
{
	pthread_t		*philo;
	t_philo			**philosopher;
	pthread_mutex_t	**forks;

	philosopher = malloc(sizeof(t_philo) * (input->philo + 1));
	if (philosopher == NULL)
		return (1);
	philo = malloc(sizeof(pthread_t) * (input->philo) + 1);
	if (philo == NULL)
	{
		free(philosopher);
		return (1);
	}
	forks = malloc(sizeof(pthread_mutex_t) * (input->philo) + 1);
	if (forks == NULL)
	{
		free(philosopher);
		free(philo);
		return (1);
	}
	creating_threads_cont(philosopher, philo, forks, input);
	joining_threads(philo, philosopher);
	return (0);
}
