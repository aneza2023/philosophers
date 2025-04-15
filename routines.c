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
    pthread_mutex_lock(phil->lfork); // waits for, could take other in meantime - possible issue
    printf("%ld %d has taken left fork\n", getting_timestamp(phil->start), phil->id);
    pthread_mutex_lock(phil->rfork);
    printf("%ld %d has taken right fork\n", getting_timestamp(phil->start), phil->id);
    printf("%ld %d is eating\n", getting_timestamp(phil->start), phil->id);
    phil->last_meal = getting_timestamp(phil->start) + phil->input->to_eat; // once he starts, he eats..not sure if correct
    usleep(phil->input->to_eat * 1000);
    phil->nb_of_meals++;
    pthread_mutex_unlock(phil->lfork);
    pthread_mutex_unlock(phil->rfork);
    return (0);
}

int phil_sleeping(t_philo *phil)
{
    
    if (getting_timestamp(phil->start) + phil->input->to_die > getting_timestamp(phil->start) + phil->input->to_sleep)
    {
        printf("%ld %d is sleeping\n", getting_timestamp(phil->start), phil->id);
        usleep(phil->input->to_sleep * 1000);
    }
    if (getting_timestamp(phil->start) + phil->input->to_die < getting_timestamp(phil->start) + phil->input->to_sleep)
    {
        printf("%ld %d is sleeping\n", getting_timestamp(phil->start), phil->id);
        usleep(phil->input->to_die * 1000);
        phil->death = 1;
        printf("%ld %d died\n", getting_timestamp(phil->start), phil->id);
    }
    return (0);
}
int phil_death(t_philo *phil)
{
    if (getting_timestamp(phil->start) > (phil->last_meal + phil->input->to_die)) // observer thread t put in
    {
        phil->death = 1;
        //printf("%ld %d died\n", getting_timestamp(phil->start), phil->id); //getting twice
    }
    return (0);
}

int continue_routine(t_philo *phil)
{
    while (phil->input->opt_meals != -1 && phil->death != 1 
        && (phil->nb_of_meals <= phil->input->opt_meals))
    {
        phil_death(phil);
        phil_eating(phil);
        phil_death(phil);
        phil_sleeping(phil);
        phil_death(phil);
        if (phil->death != 1)
            printf("%ld %d is thinking\n", getting_timestamp(phil->start), phil->id);
    }
    return (0);
}

int start_with_even(t_philo *phil)
{
    if (phil->input->opt_meals != -1 && phil->death != 1)
    {
        if (phil->id % 2 == 0)
        {
            phil_death(phil);
            phil_eating(phil);
            phil_death(phil);
            phil_sleeping(phil);
            phil_death(phil);
            if (phil->death != 1)
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
