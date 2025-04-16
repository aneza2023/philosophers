/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:55:19 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/10 18:19:46 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// to do>> if set meal nb - finish program after finishing eating or the whole cycle?

int phil_eating(t_philo *phil)
{
    if (phil->someone_died == 1 || phil->death == 1)
        return (1);
    pthread_mutex_lock(phil->lfork); // waits for, could take other in meantime - possible issue
    printf("%ld %d has taken left fork\n", getting_timestamp(phil->start), phil->id);
    pthread_mutex_lock(phil->rfork);
    printf("%ld %d has taken right fork\n", getting_timestamp(phil->start), phil->id);
    printf("%ld %d is eating\n", getting_timestamp(phil->start), phil->id);
    phil->last_meal = getting_timestamp(phil->start); // doesnt make sense to me, but should make sense to eval sheet, whatever + phil->input->to_eat
    // for that reason this bullshit
    if ((phil->last_meal + phil->input->to_die) <= (getting_timestamp(phil->start) + phil->input->to_eat))
        usleep(phil->input->to_die * 1000);
    if ((phil->last_meal + phil->input->to_die) > (getting_timestamp(phil->start) + phil->input->to_eat))
        usleep(phil->input->to_eat * 1000);
    phil->nb_of_meals++;
    pthread_mutex_unlock(phil->lfork);
    pthread_mutex_unlock(phil->rfork);
    return (0);
}

int phil_sleeping(t_philo *phil)
{
    if (phil->someone_died == 1 || phil->death == 1)
        return (1);
    if (phil->last_meal + phil->input->to_die > getting_timestamp(phil->start) + phil->input->to_sleep)
    {
        printf("%ld %d is sleeping\n", getting_timestamp(phil->start), phil->id);
        usleep(phil->input->to_sleep * 1000);
    }
    if (phil->last_meal + phil->input->to_die <= getting_timestamp(phil->start) + phil->input->to_sleep)
    {
        printf("%ld %d is sleeping\n", getting_timestamp(phil->start), phil->id);
        usleep(phil->input->to_die * 1000);
    }
    return (0);
}

int continue_routine(t_philo *phil)
{
    while (phil->input->opt_meals != -1 && phil->death != 1 
         && phil->someone_died != 1) // or someone died
    {
        if ((phil->nb_of_meals >= phil->input->opt_meals))
            break ;
        phil_eating(phil);
        phil_sleeping(phil);
        if (phil->death != 1)
            printf("%ld %d is thinking\n", getting_timestamp(phil->start), phil->id);
    }
    return (0);
}

int start_with_even(t_philo *phil)
{
    if (phil->input->opt_meals != -1 && phil->death != 1 && phil->someone_died != 1)
    {
        if (phil->id % 2 == 0)
        {
            phil_eating(phil);
            phil_sleeping(phil);
            if (phil->death != 1 && phil->someone_died != 1)
                printf("%ld %d is thinking\n", getting_timestamp(phil->start), phil->id);
        }   
        else
        {
            printf("%ld %d is thinking\n", getting_timestamp(phil->start), phil->id);
            usleep(1000);
        }
    }
    continue_routine(phil);
    return (0);
}
