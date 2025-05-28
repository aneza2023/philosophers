#include "philosophers.h"

int	locking_nb_of_meals(t_philo *philosopher)
{
	philosopher->lock_nb_meals = malloc(sizeof(pthread_mutex_t));
	if (philosopher->lock_nb_meals == NULL)
		return (1);
	pthread_mutex_init(philosopher->lock_nb_meals, NULL);
	pthread_mutex_lock(philosopher->lock_nb_meals);
	philosopher->nb_of_meals = 0;
	pthread_mutex_unlock(philosopher->lock_nb_meals);
	return (0);
}

int	locking_last_meal(t_philo *philosopher)
{
	suseconds_t	current_time;

	philosopher->lock_last_meal = malloc(sizeof(pthread_mutex_t));
	if (philosopher->lock_last_meal == NULL)
	{
		pthread_mutex_destroy(philosopher->lock_nb_meals);
		free(philosopher->lock_nb_meals);
		philosopher->lock_nb_meals = NULL;
		return (1);
	}
	current_time = gettimeofday(&philosopher->start, NULL);
	pthread_mutex_init(philosopher->lock_last_meal, NULL);
	pthread_mutex_lock(philosopher->lock_last_meal);
	philosopher->last_meal = current_time;
	pthread_mutex_unlock(philosopher->lock_last_meal);
	return (0);
}

int	locking_someone_died(t_philo *philosopher)
{
	philosopher->lock_somedeath = malloc(sizeof(pthread_mutex_t));
	if (philosopher->lock_somedeath == NULL)
	{
		pthread_mutex_destroy(philosopher->lock_nb_meals);
		free(philosopher->lock_nb_meals);
		philosopher->lock_nb_meals = NULL;
		pthread_mutex_destroy(philosopher->lock_last_meal);
		free(philosopher->lock_last_meal);
		philosopher->lock_last_meal = NULL;
		return (1);
	}
	pthread_mutex_init(philosopher->lock_somedeath, NULL);
	pthread_mutex_lock(philosopher->lock_somedeath);
	philosopher->someone_died = 0;
	pthread_mutex_unlock(philosopher->lock_somedeath);
	return (0);
}

int	adding_mutex_time(t_philo **philosophers)
{
	pthread_mutex_t *locking_time;
	int				i;

	i = 0;
	locking_time = malloc(sizeof(pthread_mutex_t));
	if (locking_time == NULL)
		return (1);
	pthread_mutex_init(locking_time, NULL);
	while(i < philosophers[0]->philo_nb)
	{
		philosophers[i]->lock_time = locking_time;
		i++;
	}
	return (0);
}


// int locking_time(t_philo *philosopher)
// {
// 	philosopher->lock_time = malloc(sizeof(pthread_mutex_t));
// 	if (philosopher->lock_time == NULL)
// 	{
// 		pthread_mutex_destroy(philosopher->lock_nb_meals);
// 		free(philosopher->lock_nb_meals);
// 		philosopher->lock_nb_meals = NULL;
// 		pthread_mutex_destroy(philosopher->lock_last_meal);
// 		free(philosopher->lock_last_meal);
// 		philosopher->lock_last_meal = NULL;
// 		pthread_mutex_destroy(philosopher->lock_somedeath);
// 		free(philosopher->lock_somedeath);
// 		philosopher->lock_somedeath = NULL;
// 		return (1);
// 	}
// 	pthread_mutex_init(philosopher->lock_time, NULL);
// 	// pthread_mutex_lock(philosopher->lock_time);
// 	// philosopher->lock_time = 0;
// 	// pthread_mutex_unlock(philosopher->lock_time);
// 	return (0);
// }
