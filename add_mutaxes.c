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
		free(philosopher->lock_nb_meals);
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
		free(philosopher->lock_nb_meals);
		free(philosopher->lock_last_meal);
		return (1);
	}
	pthread_mutex_init(philosopher->lock_somedeath, NULL);
	pthread_mutex_lock(philosopher->lock_somedeath);
	philosopher->someone_died = 0;
	pthread_mutex_unlock(philosopher->lock_somedeath);
	return (0);
}