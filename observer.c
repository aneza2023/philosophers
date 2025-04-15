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
    t_observer   *observer;

    observer = arg;
    //condition until nb of meals reached
    while (observer->philosophers[0]->someone_died != 1 && 1)
    {
        k = 0;
        while (observer->philosophers[k] != NULL)
        {
            if (observer->philosophers[k]->death == 1)
            {
                i = 0;
                while (observer->philosophers[i] != NULL)
                {
                    observer->philosophers[i]->someone_died = 1;
                    printf("KKK\n");
                    i++;
                }
            }
            k++;
        }
    }
    return (0);
}

int creating_observer(t_philo **philosophers, pthread_t *philo)
{
    t_observer   *observer;
    pthread_t    observthread;

    observer = malloc(sizeof(t_observer));
    if (observer == NULL) // need to free stuff
        return (1);
    observer->philosophers = philosophers;
    observer->philothread = philo;
    pthread_create(&observthread, NULL, observer_routine, observer);
    pthread_join(observthread, NULL);
    return (0);
}