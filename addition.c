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
		return (0);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken right fork\n", t_stamp(phil->start), phil->id);
	if (phil->rfork == phil->lfork)
		return (0);
	pthread_mutex_lock(phil->lfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
		return (0);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken left fork\n", t_stamp(phil->start), phil->id);
	return (0);
}

int	phil_not_last(t_philo *phil)
{
	pthread_mutex_lock(phil->lfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
		return (1);
	pthread_mutex_unlock(phil->lock_somedeath);
	printf("%ld %d has taken left fork\n", t_stamp(phil->start), phil->id);
	if (phil->rfork == phil->lfork)
		return (1);
	pthread_mutex_lock(phil->rfork);
	pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died == 1)
		return (1);
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
		return (1);
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




// void	*observer_routine(void *arg)
// {
// 	int			i;
// 	int			k;
// 	int			j;
// 	t_observer	*observer;

// 	observer = arg;
// 	//condition until nb of meals reached
// 	usleep((observer->philosophers[0]->input->to_die / 2) * 1000);
// 	while (observer->philosophers[0]->someone_died != 1 && 1)
// 	{
// 		k = 0;
// 		while (observer->philosophers[k] != NULL)
// 		{
// 			if (observer->philosophers[k]->nb_of_meals
//				== observer->philosophers[k]->opt_meals)
// 			{
// 				j = 1;
// 				while (observer->philosophers[j]->nb_of_meals
//					== observer->philosophers[k]->opt_meals)
// 				{
// 					j++;
// 					if (j == observer->philosophers[k]->input->philo)
// 						return (0);
// 				}
// 			}
// 			if (t_stamp(observer->philosophers[k]->start)
//				> (observer->philosophers[k]->last_meal
//					+ observer->philosophers[k]->input->to_die))
// 			{
// 				observer->philosophers[k]->death = 1;
// 				printf("%ld %d died\n",
//					t_stamp(observer->philosophers[k]->start),
//					observer->philosophers[k]->id);
// 				i = 0;
// 				while (observer->philosophers[i] != NULL)
// 				{
// 					observer->philosophers[i]->someone_died = 1;
// 					printf("KKK\n");
// 					i++;
// 				}
// 				return (1);
// 			}
// 			k++;
// 		}
// 	}
// 	return (0);
// }
