/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:49:04 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/04/06 14:50:53 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef struct input_values
{
	int	philo;
	int	to_die;
	int	to_eat;
	int	to_sleep;
	int	opt_meals;      // optional nb of meals;
}	t_val;

typedef struct philo_threads
{
	int		id;
	int		nb_of_meals;
	// int lfork;
	// int rfork;
	int		death;
	t_val	*input;
}	t_philo;


//check
int		check_for_input(char *argv, int id);
int		ft_atoi(char *argv);

//philo
int		putting_values(t_val *input, char *todie, char *toeat, char *tosleep);
int		creating_threads(t_val *input);
void	*philosophers_routine(void *arg);
int		putting_values_to_philo(t_philo *philosopher);
int		joining_threads(pthread_t *philo, t_philo **philosophers);

#endif