/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:24:44 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/04/28 23:05:36 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	phil_last(t_philo *phil)
{
	pthread_mutex_lock(phil->rfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
		return (free(phil), 1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken right fork\n", t_stamp(phil->start), phil->id);
	if (phil->rfork == phil->lfork)
		return (free(phil), 1);
	pthread_mutex_lock(phil->lfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
		return (free(phil), 1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken left fork\n", t_stamp(phil->start), phil->id);
	return (0);
}

int	phil_not_last(t_philo *phil)
{
	pthread_mutex_lock(phil->lfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
		return (free(phil), 1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken left fork\n", t_stamp(phil->start), phil->id);
	if (phil->rfork == phil->lfork)
		return (free(phil), 1);
	pthread_mutex_lock(phil->rfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
		return (free(phil), 1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken right fork\n", t_stamp(phil->start), phil->id);
	return (0);
}

int	check_order_forks(t_philo *phil)
{
	if (phil->id != phil->philo_nb)
	{
		if (phil_not_last(phil) == 1)
			return (1);
	}
	else if (phil->id == phil->philo_nb)
	{
		if (phil_last(phil) == 1)
			return (1);
	}
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
		return (free(phil), 1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d is eating\n", t_stamp(phil->start), phil->id);
	return (0);
}

int	proper_sleep(t_philo *phil)
{
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1 || phil->death == 1)
		return (1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d is sleeping\n", t_stamp(phil->start), phil->id);
	usleep(phil->to_sleep * 1000);
	return (0);
}

int allocating_first_fork(t_philo **philosopher, pthread_t *philo,
	pthread_mutex_t **forks, t_val *input)
{
	int	i;

	i = 0;
	forks[i] = malloc(sizeof(pthread_mutex_t));
	if (forks[i] == NULL)
	{
		free(philosopher);
		free(philo);
		free(forks);
		return (1);
	}
	pthread_mutex_init(forks[i], NULL);
	if (creating_threads(philosopher, philo, forks, input) == 1)
		return (1);
	return (0);
}
