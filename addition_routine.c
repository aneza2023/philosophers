/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:24:44 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/06/04 14:29:49 by ahavrank         ###   ########.fr       */
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
	printing_activity(phil, 0);
	//printf("%ld %d has taken right fork\n", t_stamp(phil), phil->id);
	if (phil->rfork == phil->lfork)
	{
		usleep(phil->to_die * 1000);
		printing_activity(phil, 4);
		//printf("%ld %d died\n", phil->to_die, phil->id);
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
	printing_activity(phil, 0);
	//printf("%ld %d has taken left fork\n", t_stamp(phil), phil->id);
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
	printing_activity(phil, 0);
	//printf("%ld %d has taken left fork\n", t_stamp(phil), phil->id);
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
	printing_activity(phil, 0);
	//printf("%ld %d has taken right fork\n", t_stamp(phil), phil->id);
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
	printing_activity(phil, 1);
	//printf("%ld %d is eating\n", t_stamp(phil), phil->id);
	return (0);	
}

int	proper_sleep(t_philo *phil)
{
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1 || phil->death == 1)
		return (pthread_mutex_unlock(phil->lock_somedeath), 1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printing_activity(phil, 2);
	//printf("%ld %d is sleeping\n", t_stamp(phil), phil->id);
	usleep(phil->to_sleep * 1000);
	return (0);
}

