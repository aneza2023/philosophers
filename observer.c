/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:52:49 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/17 15:00:28 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*observer_routine(void *arg)
{
	int			i;
	int			k;
	int			j;
	t_observer	*observer;

	observer = arg;
	//condition until nb of meals reached
	usleep((observer->philosophers[0]->input->to_die / 2) * 1000); // might optimize later
	while (observer->philosophers[0]->someone_died != 1 && 1)
	{
		k = 0;
		while (observer->philosophers[k] != NULL)
		{
			if (observer->philosophers[k]->nb_of_meals == observer->philosophers[k]->opt_meals)
			{
				j = 1;
				while (observer->philosophers[j]->nb_of_meals == observer->philosophers[k]->opt_meals)
				{
					j++;
					if (j == observer->philosophers[k]->input->philo)
						return (0);
				}
			}
			if (t_stamp(observer->philosophers[k]->start) > (observer->philosophers[k]->last_meal + observer->philosophers[k]->input->to_die))
			{
				observer->philosophers[k]->death = 1;
				printf("%ld %d died\n", t_stamp(observer->philosophers[k]->start), observer->philosophers[k]->id);
				i = 0;
				while (observer->philosophers[i] != NULL)
				{
					if (observer->philosophers[i]->rfork == observer->philosophers[i]->lfork)
						break ;
					observer->philosophers[i]->someone_died = 1;
					printf("KKK\n");
					i++;
				}
				return (1);
			}
			k++;
		}
	}
	return (0);
}

int	creating_observer(t_philo **philosophers, pthread_t *philo)
{
	t_observer	*observer;
	pthread_t	observthread;

	observer = malloc(sizeof(t_observer));
	if (observer == NULL) // need to free stuff
		return (1);
	observer->philosophers = philosophers;
	observer->philothread = philo;
	pthread_create(&observthread, NULL, observer_routine, observer);
	pthread_join(observthread, NULL);
	return (0);
}