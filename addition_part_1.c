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
	{
		pthread_mutex_unlock(phil->rfork);
		return (pthread_mutex_unlock(phil->lock_somedeath), 1);
	}
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken right fork\n", t_stamp(phil->start), phil->id);
	if (phil->rfork == phil->lfork)
	{
		usleep(phil->to_die * 1000);
		printf("%ld %d died\n", phil->to_die, phil->id);
		return (1);
	}
	phil_last_leftf(phil);
	return (0);
}

int phil_last_leftf(t_philo *phil)
{
	pthread_mutex_lock(phil->lfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
	{
		pthread_mutex_unlock(phil->rfork);
		pthread_mutex_unlock(phil->lfork);
		return (pthread_mutex_unlock(phil->lock_somedeath), 1);
	}
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken left fork\n", t_stamp(phil->start), phil->id);
	return (0);
}

int	phil_not_last(t_philo *phil)
{
	pthread_mutex_lock(phil->lfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
	{
		pthread_mutex_unlock(phil->lfork);
		return (pthread_mutex_unlock(phil->lock_somedeath), 1);
	}
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken left fork\n", t_stamp(phil->start), phil->id);
	if (phil->rfork == phil->lfork)
		return (1);
	pthread_mutex_lock(phil->rfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
	{
		pthread_mutex_unlock(phil->lfork);
		pthread_mutex_unlock(phil->rfork);
		return (pthread_mutex_unlock(phil->lock_somedeath), 1);
	}
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
		return (pthread_mutex_unlock(phil->lock_somedeath), 1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d is eating\n", t_stamp(phil->start), phil->id);
	return (0);
}

int	proper_sleep(t_philo *phil)
{
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1 || phil->death == 1)
		return (pthread_mutex_unlock(phil->lock_somedeath), 1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d is sleeping\n", t_stamp(phil->start), phil->id);
	usleep(phil->to_sleep * 1000);
	return (0);
}

