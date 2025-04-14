/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oberver.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:52:49 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/10 18:13:32 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *observer_routine(void *arg)
{
    int     i;
    int     k;
    t_philo **philosophers;

    philosophers = arg;
    i = 0;
    k = 0;
    while (philosophers[k] != NULL)
    {
        if (philosophers[k]->death == 1)
        {
            while (philosophers[i] != NULL)
            {
                philosophers[i]->someone_died = 1;
                i++;
            }
        }
        printf("PHILL %d MEALS %d", philosophers[k]->id, philosophers[k]->nb_of_meals);
        k++;
    }
    return (0);
}

int creating_observer(t_philo **philosophers, pthread_t *philo)
{
    t_observer   observer;
    pthread_t    observthread;

    observer->philosophers = philosophers;
    observer->philothread = philo;
    pthread_create(&observthread, NULL, observer_routine, philosophers);
    pthread_join(observer, NULL);
    return (0);
}