/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oberver.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:52:49 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/10 17:07:51 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *observer_routine(void *arg)
{
    int     i;
    int     status;
    t_philo **philosophers;

    philosophers = arg;
    i = 0;
    status = 0;
    while (philosophers[status] != '\0')
    {
        if (philosophers[status]->death == 1)
        {
            while (i <= status)
            {
                philosophers[i]->someone_died = 1;
                i++;
            }
            while (philosophers[i] != '\0')
            {
                philosophers[i]->someone_died = 1;
                i++;
            }
        }
        i++;
    }
    return (0);
}

int creating_observer(t_philo **philosophers)
{
    pthread_t   observer;

    // observer = malloc(sizeof(pthread_t));
    // if (observer == NULL)
    //     return (1);
    pthread_create(&observer, NULL, observer_routine, philosophers);
    return (0);
}