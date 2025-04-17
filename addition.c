/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:24:44 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/04/17 20:24:41 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	phil_last(t_philo *phil)
{
	pthread_mutex_lock(phil->rfork);
	if (phil->someone_died == 1 || phil->death == 1)
		return (1);
	printf("%d %d has taken right fork\n", t_stamp(phil->start), phil->id);
	if (phil->rfork == phil->lfork)
		return (0);
	pthread_mutex_lock(phil->lfork);
	if (phil->someone_died == 1 || phil->death == 1)
		return (1);
	printf("%d %d has taken left fork\n", t_stamp(phil->start), phil->id);
	return (0);
}

int	check_order_forks(t_philo *phil)
{
	if (phil->id != phil->input->philo)
	{
		pthread_mutex_lock(phil->lfork);
		if (phil->someone_died == 1 || phil->death == 1)
			return (1);
		printf("%d %d has taken left fork\n", t_stamp(phil->start), phil->id);
		if (phil->rfork == phil->lfork)
			return (0);
		pthread_mutex_lock(phil->rfork);
		if (phil->someone_died == 1 || phil->death == 1)
			return (1);
		printf("%d %d has taken right fork\n", t_stamp(phil->start), phil->id);
	}
	else if (phil->id == phil->input->philo)
		phil_last(phil);
	if (phil->someone_died == 1 || phil->death == 1)
		return (1);
	printf("%d %d is eating\n", t_stamp(phil->start), phil->id);
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
