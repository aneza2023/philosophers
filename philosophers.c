
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
    t_val   *input;

    if (argc <= 4 || argc >= 7)
    {
        write (1, "Error\n", 6);
        return (1);
    }
    while (argc > 1)
    {
        if (check_for_input(argv[argc - 1], (argc - 1)) == 1)
        {
            write (1, "Error\n", 6);
            return (1);
        }
        argc--;
    }
    input = malloc(sizeof(t_val));
    if (input == NULL) // do i need to write error? could write fce before return na prasaka
        return (1);
    input->philo = ft_atoi(argv[1]);
    if (argv[5] != NULL)
        input->opt_meals = ft_atoi(argv[5]);
    if (philosophers(input, argv[2], argv[3], argv[4]) == 1) // this kind of check up needed??
        return (1);
    return (0);
}
