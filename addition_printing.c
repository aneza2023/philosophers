/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_printing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:32:28 by ahavrank          #+#    #+#             */
/*   Updated: 2025/06/07 15:35:11 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int printing_activity(t_philo *phil, int activity)
{
    if (activity == 0)
        printing(phil, "has taken a fork");
    if (activity == 1)
        printing(phil, "is eating");
    if (activity == 2)
        printing(phil, "is sleeping");
    if (activity == 3)
        printing(phil, "is thinking");
    return (0);
}

int printing(t_philo *phil, char *string)
{
    pthread_mutex_lock(phil->lock_somedeath);
    pthread_mutex_lock(phil->lock_time);
	if (phil->someone_died != 1 && phil->rfork != phil->lfork)
		printf("%ld %d %s\n", t_stamp(phil), phil->id, string);
	pthread_mutex_unlock(phil->lock_somedeath);
    pthread_mutex_unlock(phil->lock_time);
    return (0);
}
