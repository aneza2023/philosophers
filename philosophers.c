
#include "philosophers.h"

int putting_values(t_val *input, char *todie, char *toeat, char *tosleep)
{
    input->to_die = ft_atoi(todie);
    input->to_eat = ft_atoi(toeat);
    input->to_sleep = ft_atoi(tosleep);
    return (0);
}

int philosophers(t_val *input, char *todie, char *toeat, char *tosleep)
{
    //printf("%d", input->philo);
    putting_values(input, todie, toeat, tosleep);
    creating_threads(input);
    return (0);
}

int main(int argc, char *argv[])
{
    int     i;
    t_val   *input;

    i = 1;
    if (argc <= 4 || argc >= 7)
    {
        write (1, "Error\n", 6);
        return (1);
    }
    while (i <= argc - 1)
    {
        if (check_for_input(argv[i], i) == 1)
        {
            write (1, "Error\n", 6);
            return (1);
        }
        i++;
    }
    input = malloc(sizeof(t_val));
    if (input == NULL) // do i need to write error? could write fce before return na prasaka
        return (1);
    input->philo = ft_atoi(argv[1]);
    // input->optional = ft_atoi(argv[5])
    philosophers(input, argv[2], argv[3], argv[4]);
    return (0);
}
