/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:49:04 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/04/17 19:40:57 by anezkahavra      ###   ########.fr       */
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
	int			philo;
	suseconds_t	to_die;
	int			to_eat;
	int			to_sleep;
	int			opt_meals;
}	t_val;

typedef struct philo_threads
{
	int				id;
	pthread_mutex_t	*lock_some_died; // in process
	int				nb_of_meals;
	pthread_mutex_t	*lock_nb_meals; // in process
	int				nb_of_sleep;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	int				death;
	pthread_mutex_t	*lock_death; // add
	t_val			*input;
	int				philo_nb;
	int				someone_died;
	pthread_mutex_t	*lock_somedeath;
	struct timeval	start;
	suseconds_t		last_meal;
	pthread_mutex_t	*lock_last_meal; // in process
	suseconds_t		to_die;
	suseconds_t		to_eat;
	suseconds_t		to_sleep;
	int				opt_meals;
	pthread_mutex_t	*lock_opt_meals;
}	t_philo;

typedef struct observer
{
	t_philo		**philosophers;
	pthread_t	*philothread; // probably because of nb of lines needs to add nb of philo / checked in observer, lock would take too much space
}	t_observer;

//check
int				check_for_input(char *argv, int id);
int				ft_atoi(char *argv);

//philo
int				putting_values(t_val *input, char *todie,
					char *toeat, char *tosleep);
int				allocate_for_threads(t_val *input);
void			*philosophers_routine(void *arg);
int				putting_val_phil(t_philo *philosopher);
int				joining_threads(pthread_t *philo, t_philo **philosophers);
suseconds_t		t_stamp(struct timeval original_time);
int				start_with_even(t_philo *philosopher);
int				phil_eating(t_philo *phil);
int				phil_sleeping(t_philo *phil);
int				phil_death(t_philo *phil);
int				continue_routine(t_philo *phil);
int				check_order_forks(t_philo *phil);
int				creating_threads(t_philo **philosopher, pthread_t *philo,
					pthread_mutex_t **forks, t_val *input);
int				allocating_first_fork(t_philo **philosopher, pthread_t *philo,
					pthread_mutex_t **forks, t_val *input);
int				phil_last(t_philo *phil);
int				help_ftusleep();
int				ft_usleep(int milisec);
int				adding_forks(t_philo **philosopher, pthread_mutex_t **forks, int id);
int				proper_sleep(t_philo *phil);

//observer
int				creating_observer(t_philo **philosophers, pthread_t *philo);
void			*observer_routine(void *arg);

// free stuff
int				free_forks(t_philo **philosopher, pthread_mutex_t **forks, int id);
int				free_philosopher(t_philo **philosopher, pthread_t *philo,
					pthread_mutex_t **forks, int id);
void    		free_finish(t_philo **phil, pthread_t *philos, pthread_mutex_t **forks);
void    		free_mutaxes(t_philo *phil);

//mutaxes
int				locking_nb_of_meals(t_philo *philosopher);
int				locking_last_meal(t_philo *philosopher);
int				locking_someone_died(t_philo *philosopher);

#endif