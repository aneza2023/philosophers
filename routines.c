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

int continue_routine(t_philo *phil)
{
    while (phil->input->opt_meals != -1 && phil->someone_died != 1 && (phil->nb_of_meals <= phil->input->opt_meals))
    {
        //delete later >> observer fix
        if (getting_timestamp(phil->start) >= (phil->last_meal + phil->input->to_die)) // observer thread t put in
        {
            phil->death = 1;
            printf("DIED phil nb %d\n", phil->id);
            break ;
        }
        //printf("\ndeatSTART>> %d\n", phil->start);
        // printf("\ndeatLASTMEAL>> %ld\n", phil->last_meal);
        // printf("\ndeatTODIE>> %d\n", phil->input->to_die);
        pthread_mutex_lock(phil->lfork);
        printf("%ld %d has taken left fork\n", getting_timestamp(phil->start), phil->id);
        pthread_mutex_lock(phil->rfork);
        printf("%ld %d has taken right fork\n", getting_timestamp(phil->start), phil->id);
        printf("%ld %d is eating\n", getting_timestamp(phil->start), phil->id);
        usleep(phil->input->to_eat * 1000);
        phil->nb_of_meals++;
        phil->last_meal = getting_timestamp(phil->start);
        pthread_mutex_unlock(phil->lfork);
        pthread_mutex_unlock(phil->rfork);
        printf("%ld %d is sleeping\n", getting_timestamp(phil->start), phil->id);
        usleep(phil->input->to_sleep * 1000);
        printf("%ld %d is thinking\n", getting_timestamp(phil->start), phil->id);
    }
    return (0);
}

int start_with_even(t_philo *phil)
{
    if (phil->input->opt_meals != -1)
    {
        if (phil->id % 2 == 0)
        {
            pthread_mutex_lock(phil->lfork);
            printf("%ld %d has taken left fork\n", getting_timestamp(phil->start), phil->id);
            pthread_mutex_lock(phil->rfork);
            printf("%ld %d has taken right fork\n", getting_timestamp(phil->start), phil->id);
            printf("%ld %d is eating\n", getting_timestamp(phil->start), phil->id);
            usleep(phil->input->to_eat * 1000);
            phil->nb_of_meals++;
            pthread_mutex_unlock(phil->lfork);
            pthread_mutex_unlock(phil->rfork);
            printf("%ld %d is sleeping\n", getting_timestamp(phil->start), phil->id);
		    usleep(phil->input->to_sleep * 1000);
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
