/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:55:19 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/17 20:27:19 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//if set meal nb - finish program after finishing eating or the whole cycle?
// waits for, could take other in meantime - possible issue - forks management

//phil->last_meal = t_stamp(phil->start); 
//doesnt make sense to me, makes sense to eval sheet, whatever

int	phil_eating(t_philo *phil)
{
	check_order_forks(phil);
	phil->last_meal = t_stamp(phil->start);
	if (phil->last_meal + phil->to_die <= t_stamp(phil->start) + phil->to_eat)
		usleep(phil->to_die * 1000);
	if (phil->last_meal + phil->to_die > t_stamp(phil->start) + phil->to_eat)
		usleep(phil->to_eat * 1000);
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
		return (0);
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
		&& phil->someone_died != 1 /* && phil->nb_of_meals != phil->opt_meals */)
	{
		pthread_mutex_lock(phil->lock_nb_meals);
		if (phil->nb_of_meals == phil->opt_meals)
			break ;
		pthread_mutex_unlock(phil->lock_nb_meals);
		phil_eating(phil);
		if (phil->rfork == phil->lfork)
			return (1);
		phil_sleeping(phil);
		if (phil->death != 1 && phil->someone_died != 1
			&& phil->rfork != phil->lfork)
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
			if (phil->rfork != phil->lfork)
			{
				printf("%ld %d is thinking\n", t_stamp(phil->start), phil->id);
				usleep((phil->to_eat / 2) * 1000);
			}
		}
	}
	continue_routine(phil);
	return (0);
}

//before creating threads, should be ok >> mutaxes

int	putting_val_phil(t_philo *philosopher)
{
	suseconds_t	current_time;
// philosopher, forks, alocated, philo

	philosopher->lock_nb_meals = malloc(sizeof(pthread_mutex_t));
	//philosopher->lock_opt_meals = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philosopher->lock_nb_meals, NULL);
	pthread_mutex_lock(philosopher->lock_nb_meals);
	philosopher->nb_of_meals = 0;
	pthread_mutex_unlock(philosopher->lock_nb_meals);
	philosopher->nb_of_sleep = 0;
	philosopher->death = 0;
	philosopher->someone_died = 0;
	philosopher->to_die = philosopher->input->to_die;
	philosopher->to_eat = philosopher->input->to_eat;
	philosopher->to_sleep = philosopher->input->to_sleep;
	//pthread_mutex_init(philosopher->lock_opt_meals, NULL);
	//pthread_mutex_lock(philosopher->lock_opt_meals);
	philosopher->opt_meals = philosopher->input->opt_meals;
	//pthread_mutex_unlock(philosopher->lock_opt_meals);
	current_time = gettimeofday(&philosopher->start, NULL);
	philosopher->last_meal = current_time;
	return (0);
}
