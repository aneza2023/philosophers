/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:52:49 by ahavrank          #+#    #+#             */
/*   Updated: 2025/06/02 12:15:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_somedeath);
	philo->someone_died = 1;
	pthread_mutex_unlock(philo->lock_somedeath);
	return (0);
}

int	check_for_meals(t_observer *observer)
{
	static int	i;
	int	j;
	
	pthread_mutex_lock(observer->philosophers[i]->lock_nb_meals);
	if (observer->philosophers[0]->opt_meals != -2 && observer->philosophers[0 + i]->nb_of_meals
		>= observer->philosophers[0]->opt_meals)
	{
		pthread_mutex_unlock(observer->philosophers[i]->lock_nb_meals);
		i++;
	}
	else 
		pthread_mutex_unlock(observer->philosophers[i]->lock_nb_meals);
	if (i >= observer->philosophers[0]->philo_nb - 1)
	{
		j = 0;
		while (observer->philosophers[j] != NULL)
		{
			someone_died(observer->philosophers[j]);
			j++;
		}
		return (1);
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
		pthread_mutex_lock(observer->philosophers[k]->lock_last_meal);
		if (t_stamp(observer->philosophers[k])
			> (observer->philosophers[k]->last_meal
				+ observer->philosophers[k]->to_die))
		{
			i = 0;
			while (observer->philosophers[i] != NULL)
			{
				someone_died(observer->philosophers[i]);
				i++;
			}
			usleep(100);
			printf("%ld %d died\n", t_stamp(observer->philosophers[k]),
				observer->philosophers[k]->id);
			return (pthread_mutex_unlock(observer->philosophers[k]->lock_last_meal), 1);
		}
		pthread_mutex_unlock(observer->philosophers[k]->lock_last_meal);
		k++;
	}
	return (0);
}

void	*observer_routine(void *arg)
{
	t_observer	*observer;

	observer = arg;
	usleep((observer->philosophers[0]->input->to_die / 2) * 1000); //maybe optimize
	while (1)
	{
		if (check_for_meals(observer) == 1)
			return (NULL);
		if (check_for_death(observer) == 1)
			return (NULL);
	}
	return (NULL);
}

int	creating_observer(t_philo **philosophers, pthread_t *philo)
{
    int i;
    t_observer  *observer;
	pthread_t	observthread;

    i = 0;
    observer = malloc(sizeof(t_observer)); //memory works until here
	if (observer == NULL)
        return (1);
	philosophers[philosophers[0]->philo_nb] = NULL;
	observer->philosophers = philosophers;
	observer->philothread = philo;
	if (adding_mutex_time(philosophers) == 1)
		return (free(observer), 1);
    while(i < philosophers[0]->philo_nb)
    {
        pthread_create(&philo[i], NULL, philosophers_routine, philosophers[i]);
        i++;
    }
	pthread_create(&observthread, NULL, observer_routine, observer);
	joining_threads(philo, philosophers);
	pthread_join(observthread, NULL);
	free(observer);
	return (0);
}
