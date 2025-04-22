/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:52:49 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/17 20:26:18 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_for_meals(t_observer *observer)
{
	int	i;
	int	j;

	i = 0;
	while (observer->philosophers[i] != NULL)
	{
		if (observer->philosophers[i]->nb_of_meals
			== observer->philosophers[i]->opt_meals)
		{
			j = 1;
			while (observer->philosophers[j]->nb_of_meals
				== observer->philosophers[i]->opt_meals)
			{
				j++;
				if (j == observer->philosophers[i]->input->philo)
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_for_death(t_observer *observer)
{
	int	k;
	int	i;

	k = 0;
	while (observer->philosophers[k] != NULL)
	{
		if (t_stamp(observer->philosophers[k]->start)
			> (observer->philosophers[k]->last_meal
				+ observer->philosophers[k]->input->to_die))
		{
			observer->philosophers[k]->death = 1;
			printf("%ld %d died\n", t_stamp(observer->philosophers[k]->start),
				observer->philosophers[k]->id);
			i = 0;
			while (observer->philosophers[i] != NULL)
			{
				observer->philosophers[i]->someone_died = 1;
				printf("KKK\n");
				i++;
			}
			return (1);
		}
		k++;
	}
	return (0);
}

void	*observer_routine(void *arg)
{
	t_observer	*observer;

	observer = arg;
	usleep((observer->philosophers[0]->input->to_die / 2) * 1000);
	while (1)
	{
		if (check_for_meals(observer) == 1)
			return (NULL);
		if (check_for_death(observer) == 1)
			return (NULL);
	}
	return (NULL);
}

// need to free stuff

int	creating_observer(t_philo **philosophers, pthread_t *philo)
{
	t_observer	*observer;
	pthread_t	observthread;

	observer = malloc(sizeof(t_observer));
	if (observer == NULL)
		return (1);
	observer->philosophers = philosophers;
	observer->philothread = philo;
	pthread_create(&observthread, NULL, observer_routine, observer);
	pthread_join(observthread, NULL);
	return (0);
}
