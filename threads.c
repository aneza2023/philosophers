/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:54:51 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/28 23:05:31 by anezkahavra      ###   ########.fr       */
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
	if (start_with_even(philosopher) == 1)
		return (NULL);
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

int	creating_threads(t_philo **philosopher, pthread_t *philo,
	pthread_mutex_t **forks, t_val *input)
{
	int	i;

	i = 0;
	while (i < input->philo)
	{
		philosopher[i] = malloc(sizeof(t_philo));
		if (philosopher[i] == NULL)
		{
			free_philosopher(philosopher, philo, forks, i);
			return (1);
		}
		memset(philosopher[i], 0, sizeof(t_philo));
		philosopher[i]->input = input;
		if (adding_forks(philosopher, forks, i) == 1)
			return (free(philo), 1);
		if (putting_val_phil(philosopher[i]) == 1)
			return (free_finish(philosopher, philo, forks, input), 1);
		pthread_create(&philo[i], NULL, philosophers_routine, philosopher[i]);
		i++;
	}
	if (creating_observer(philosopher, philo) == 1) 
		return (1);
	free_finish(philosopher, philo, forks, input);
	return (0);
}

int	allocate_for_threads(t_val *input)
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
	if (allocating_first_fork(philosopher, philo, forks, input) == 1)
		return (1);
	joining_threads(philo, philosopher);
	return (0);
}
