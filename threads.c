#include "philosophers.h"

suseconds_t  getting_timestamp(suseconds_t original_time)
{
	struct timeval	current_time;
	suseconds_t		curr;

	gettimeofday(&current_time, NULL);
	curr = current_time.tv_usec - original_time;
	curr = curr / 1000;
	return(curr);
}

void *philosophers_routine(void *arg) // issue might be using just susecond, might use both = timestamp does not work
{
	t_philo 	*philosopher;
	suseconds_t	current_time; //struct timeval might be needed

	philosopher = (t_philo *)arg;
	//printf ("philo %d here\n", philosopher->id);
	philosopher->nb_of_meals = 0;
	philosopher->death = 0;
	gettimeofday(&philosopher->start, NULL);
	current_time = getting_timestamp(philosopher->start.tv_usec);
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(philosopher->lfork);
		printf("%ld %d has taken left fork\n", getting_timestamp(philosopher->start.tv_usec), philosopher->id);
		pthread_mutex_lock(philosopher->rfork);
		printf("%ld %d has taken right fork\n", getting_timestamp(philosopher->start.tv_usec), philosopher->id);
		printf("%ld %d is eating\n", getting_timestamp(philosopher->start.tv_usec), philosopher->id);
		usleep(philosopher->input->to_eat * 1000);
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
		printf("%ld %d is sleeping\n", getting_timestamp(philosopher->start.tv_usec), philosopher->id);
		usleep(philosopher->input->to_sleep * 1000);
		printf("%ld %d is thinking\n", getting_timestamp(philosopher->start.tv_usec), philosopher->id);
	}

	//printf("\n%ld\n", current_time);
	return (NULL);
}

int	joining_threads(pthread_t *philo, t_philo **philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers[0]->input->philo)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (1);
}

int creating_threads_cont(t_philo **philosopher, pthread_t *philo, pthread_mutex_t **forks, t_val *input)
{
	int i;

	i = 0;
	forks[i] = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(forks[i], NULL);
	while (i < input->philo)
	{
		philosopher[i] = malloc(sizeof(t_philo));  //free needed, allocation failed

		memset(philosopher[i], 0, sizeof(t_philo));
		philosopher[i]->id = i + 1;
		philosopher[i]->input = input;
		forks[i + 1] = malloc(sizeof(pthread_mutex_t)); //free needed if allocation failed
		pthread_mutex_init(forks[i + 1], NULL);
		philosopher[i]->lfork = forks[i];
		if (i != input->philo - 1)
			philosopher[i]->rfork = forks[i + 1];
		if (i == input->philo - 1)
			philosopher[i]->rfork = forks[0];
		pthread_create(&philo[i], NULL, philosophers_routine, philosopher[i]);
		i++;
	}
	return (0);
}

int creating_threads(t_val *input)
{
	pthread_t *philo;
	t_philo   **philosopher;
	pthread_mutex_t **forks;

	philosopher = malloc(sizeof(t_philo) * (input->philo + 1));
	if (philosopher == NULL)
		return(1);
	philo = malloc(sizeof(pthread_t) * (input->philo) + 1);
	if (philo == NULL)
	{
		free(philosopher);
		return(1);
	}
	forks = malloc(sizeof(pthread_mutex_t) * (input->philo) + 1);
	if (forks == NULL)
	{
		free(philosopher);
		free(philo);
		return(1);
	}
	creating_threads_cont(philosopher, philo, forks, input);
	joining_threads(philo, philosopher);
	return (0);
}
