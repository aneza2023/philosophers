#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct input_values
{
    int philo;
    int to_die;
    int to_eat;
    int to_sleep;
    // optional nb of meals;
}   t_val;

// typedef struct philo_threads
// {
//     int id;
// }   t_thread;


//check
int check_for_input(char *argv, int id);
int ft_atoi(char *argv);

//philo
int putting_values(t_val *input, char *todie, char *toeat, char *tosleep);
int creating_threads(t_val *input);
void *philosophers_routine(void *arg);

#endif