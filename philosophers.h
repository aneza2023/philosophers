/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:49:04 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/04/10 17:01:30 by ahavrank         ###   ########.fr       */
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
	int				nb_of_sleep;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	int				death;
	t_val			*input;
	int 			someone_died;
	struct timeval 	start;
	suseconds_t		last_meal;
}	t_philo;


//check
int				check_for_input(char *argv, int id);
int				ft_atoi(char *argv);

//philo
int				putting_values(t_val *input, char *todie, char *toeat, char *tosleep);
int				creating_threads(t_val *input);
void			*philosophers_routine(void *arg);
int				putting_values_to_philo(t_philo *philosopher);
int				joining_threads(pthread_t *philo, t_philo **philosophers);
suseconds_t		getting_timestamp(struct timeval original_time);
int				start_with_even(t_philo *philosopher);

//observer
int				creating_observer(t_philo **philosophers);
void 			*observer_routine(void *arg);

#endif