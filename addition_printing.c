/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_printing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:32:28 by ahavrank          #+#    #+#             */
/*   Updated: 2025/06/04 14:30:38 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int printing_activity(t_philo *phil, int activity)
{
    char *string;
    int stringlen;

    if (activity == 0)
        stringlen = ft_strlen("has taken a fork");
    if (activity == 1)
        stringlen = ft_strlen("is eating");
    if (activity == 2 || activity == 3)
        stringlen = ft_strlen("is sleeping");
    if (activity == 4)
        stringlen = ft_strlen("died");
    string = malloc(sizeof(char) * stringlen);
    if (string == NULL)
        return (1);
    if (activity == 0)
        string = "has taken a fork";
    if (activity == 1)
        string = "is eating";
    if (activity == 2)
        string ="is sleeping";
    if (activity == 3)
        string = "is thinking";
    printing(phil, string, activity);
    return (0);
}

int printing(t_philo *phil, char *string, int activity)
{
    if (activity == 4)
        string = "died";
    pthread_mutex_lock(phil->lock_somedeath);
	if (phil->someone_died != 1 && phil->rfork != phil->lfork)
		printf("%ld %d %s\n", t_stamp(phil), phil->id, string);
	pthread_mutex_unlock(phil->lock_somedeath);
    return (0);
}
