/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:55:19 by ahavrank          #+#    #+#             */
/*   Updated: 2025/06/04 14:37:56 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//if set meal nb - finish program after finishing eating or the whole cycle?
// waits for, could take other in meantime - possible issue - forks management

//phil->last_meal = t_stamp(phil->start); 
//doesnt make sense to me, makes sense to eval sheet, whatever

int	phil_eating(t_philo *phil)
{
	if (check_order_forks(phil) == 1)
		return (1);
	pthread_mutex_lock(phil->lock_last_meal);
	phil->last_meal = t_stamp(phil);
	if (phil->last_meal + phil->to_die <= t_stamp(phil) + phil->to_eat)
	{
		pthread_mutex_unlock(phil->lock_last_meal);
		usleep(phil->to_die * 1000);
	}
	if (phil->last_meal + phil->to_die > t_stamp(phil) + phil->to_eat)
	{
		pthread_mutex_unlock(phil->lock_last_meal);
		usleep(phil->to_eat * 1000);
	}
	pthread_mutex_lock(phil->lock_nb_meals);
	phil->nb_of_meals++;
	pthread_mutex_unlock(phil->lock_nb_meals);
	pthread_mutex_unlock(phil->lfork);
	pthread_mutex_unlock(phil->rfork);
	return (0);
}

int	phil_sleeping(t_philo *phil)
{
	if (phil->rfork == phil->lfork)
		return (1);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
		return (pthread_mutex_unlock(phil->lock_somedeath), 1);
	pthread_mutex_unlock(phil->lock_somedeath);
	pthread_mutex_lock(phil->lock_last_meal);
	if (phil->last_meal + phil->to_die > t_stamp(phil) + phil->to_sleep)
	{
		pthread_mutex_unlock(phil->lock_last_meal);
		if (proper_sleep(phil) == 1)
			return (1);
	}
	else if (phil->last_meal + phil->to_die
		<= t_stamp(phil) + phil->to_sleep)
	{
		pthread_mutex_unlock(phil->lock_last_meal);
		pthread_mutex_lock(phil->lock_somedeath);
		if (phil->someone_died == 1 || phil->death == 1)
			return (pthread_mutex_unlock(phil->lock_somedeath), 1);
		pthread_mutex_unlock(phil->lock_somedeath);
		printing_activity(phil, 2);
		//printf("%ld %d is sleeping\n", t_stamp(phil), phil->id);
		usleep(phil->to_die * 1000);
	}
	return (0);
}

int	continue_routine(t_philo *phil)
{
	pthread_mutex_lock(phil->lock_somedeath);
	pthread_mutex_lock(phil->lock_nb_meals);
	while (phil->someone_died != 1)
	{
		pthread_mutex_unlock(phil->lock_nb_meals);
		pthread_mutex_unlock(phil->lock_somedeath);
		if (phil_eating(phil) == 1)
			return (1);
		if (phil->rfork == phil->lfork)
			return (1);
		if (phil_sleeping(phil) == 1)
			return (1);
		pthread_mutex_lock(phil->lock_somedeath);
		if (phil->someone_died != 1 && phil->rfork != phil->lfork)
		{
			//printf("%ld %d is thinking\n", t_stamp(phil), phil->id);
			pthread_mutex_unlock(phil->lock_somedeath);
			printing_activity(phil, 3);
			usleep(1000);
			pthread_mutex_lock(phil->lock_somedeath);
		}
		pthread_mutex_lock(phil->lock_nb_meals);
	}
	pthread_mutex_unlock(phil->lock_somedeath);
	pthread_mutex_unlock(phil->lock_nb_meals);
	return (0);
}

int	start_with_even(t_philo *phil)
{
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died != 1)
	{
		pthread_mutex_unlock(phil->lock_somedeath);
		if (phil->id % 2 == 0)
		{
			if (phil_eating(phil) == 1)
				return (1);
			if (phil_sleeping(phil) == 1)
				return (1);
		}
		printing_activity(phil, 3);
		usleep(phil->to_die / 4 * 1000); // ADDED THIS MIGHT BE ISSUE LATER, TEST AT 42
		// pthread_mutex_lock(phil->lock_somedeath);
		// if (phil->someone_died != 1 && phil->rfork != phil->lfork)
		// 	printf("%ld %d is thinking\n", t_stamp(phil), phil->id);
		// pthread_mutex_unlock(phil->lock_somedeath);
		if (phil->id % 2 != 0 && phil->rfork != phil->lfork)
			usleep((phil->to_eat / 2) * 1000);
	}
	if (continue_routine(phil) == 1)
		return (1);
	return (0);
}

int	putting_val_phil(t_philo *philosopher)
{
	if (locking_nb_of_meals(philosopher) == 1)
		return (1);
	if (locking_last_meal(philosopher) == 1)
		return (1);
	if (locking_someone_died(philosopher) == 1)
		return (1);
	philosopher->nb_of_sleep = 0;
	philosopher->death = 0;
	philosopher->nb_of_meals = 0;
	philosopher->philo_nb = philosopher->input->philo;
	philosopher->to_die = philosopher->input->to_die;
	philosopher->to_eat = philosopher->input->to_eat;
	philosopher->to_sleep = philosopher->input->to_sleep;
	philosopher->opt_meals = philosopher->input->opt_meals;
	return (0);
}
