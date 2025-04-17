/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:55:19 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/17 13:04:24 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// to do>> if set meal nb - finish program after finishing eating or the whole cycle?
 // waits for, could take other in meantime - possible issue - forks management

int	phil_eating(t_philo *phil)
{
	pthread_mutex_lock(phil->lfork);
	if (phil->someone_died == 1 || phil->death == 1)
		return (1);
	printf("%ld %d has taken left fork\n", t_stamp(phil->start), phil->id);
	pthread_mutex_lock(phil->rfork);
	if (phil->someone_died == 1 || phil->death == 1)
		return (1);
	printf("%ld %d has taken right fork\n", t_stamp(phil->start), phil->id);
	if (phil->someone_died == 1 || phil->death == 1)
		return (1);
	printf("%ld %d is eating\n", t_stamp(phil->start), phil->id);
	phil->last_meal = t_stamp(phil->start); // doesnt make sense to me, but should make sense to eval sheet, whatever ->to_eat
	// for that reason this bullshit
	if (phil->last_meal + phil->to_die <= t_stamp(phil->start) + phil->to_eat)
		usleep(phil->to_die * 1000);
	if (phil->last_meal + phil->to_die > t_stamp(phil->start) + phil->to_eat)
		usleep(phil->to_eat * 1000);
	phil->nb_of_meals++;
	pthread_mutex_unlock(phil->lfork);
	pthread_mutex_unlock(phil->rfork);
	return (0);
}

int	phil_sleeping(t_philo *phil)
{
	if (phil->someone_died == 1 || phil->death == 1)
		return (1);
	if (phil->last_meal + phil->to_die > t_stamp(phil->start) + phil->to_sleep)
	{
		if (phil->someone_died == 1 || phil->death == 1)
			return (1);
		printf("%ld %d is sleeping\n", t_stamp(phil->start), phil->id);
		usleep(phil->to_sleep * 1000);
	}
	else if (phil->last_meal + phil->to_die
		<= t_stamp(phil->start) + phil->to_sleep)
	{
		if (phil->someone_died == 1 || phil->death == 1)
			return (1);
		printf("%ld %d is sleeping\n", t_stamp(phil->start), phil->id);
		usleep(phil->to_die * 1000);
	}
	return (0);
}

int	continue_routine(t_philo *phil)
{
	while (phil->opt_meals != -1 && phil->death != 1
		&& phil->someone_died != 1)
	{
		if ((phil->nb_of_meals == phil->opt_meals))
			break ;
		phil_eating(phil);
		phil_sleeping(phil);
		if (phil->death != 1 && phil->someone_died != 1)
			printf("%ld %d is thinking\n", t_stamp(phil->start), phil->id);
	}
	return (0);
}

int	start_with_even(t_philo *phil)
{
	if (phil->opt_meals != -1 && phil->death != 1 && phil->someone_died != 1)
	{
		if (phil->id % 2 == 0)
		{
			phil_eating(phil);
			phil_sleeping(phil);
			if (phil->death != 1 && phil->someone_died != 1)
				printf("%ld %d is thinking\n", t_stamp(phil->start), phil->id);
		}
		else
		{
			if (phil->someone_died == 1 || phil->death == 1)
				return (1);
			printf("%ld %d is thinking\n", t_stamp(phil->start), phil->id);
			usleep(1000);
		}
	}
	continue_routine(phil);
	return (0);
}
