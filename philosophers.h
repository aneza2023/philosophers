/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:49:04 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/04/09 17:25:32 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

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
	int				id;
	int				nb_of_meals;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	int				death;
	t_val			*input;
	struct timeval 	start;	
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
suseconds_t  getting_timestamp(suseconds_t original_time);

#endif