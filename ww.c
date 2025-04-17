/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ww.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:24:44 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/04/17 15:30:25 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_order_forks(t_philo *phil)
{
    if (phil->id != phil->input->philo)
    {
        pthread_mutex_lock(phil->lfork);
        if (phil->someone_died == 1 || phil->death == 1)
            return (1);
        printf("%ld %d has taken left fork\n", t_stamp(phil->start), phil->id);
        if (phil->rfork == phil->lfork)
            return (0);
        pthread_mutex_lock(phil->rfork);
        if (phil->someone_died == 1 || phil->death == 1)
            return (1);
        printf("%ld %d has taken right fork\n", t_stamp(phil->start), phil->id);
        if (phil->someone_died == 1 || phil->death == 1)
            return (1);
        printf("%ld %d is eating\n", t_stamp(phil->start), phil->id);
    }
    else
    {
        pthread_mutex_lock(phil->rfork);
        if (phil->someone_died == 1 || phil->death == 1)
            return (1);
        printf("%ld %d has taken right fork\n", t_stamp(phil->start), phil->id);
        if (phil->rfork == phil->lfork)
            return (0);
        pthread_mutex_lock(phil->lfork);
        if (phil->someone_died == 1 || phil->death == 1)
            return (1);
        printf("%ld %d has taken left fork\n", t_stamp(phil->start), phil->id);
        if (phil->someone_died == 1 || phil->death == 1)
            return (1);
        printf("%ld %d is eating\n", t_stamp(phil->start), phil->id);
    }
    return (0);
}
