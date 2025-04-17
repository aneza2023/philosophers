/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:25:50 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/17 12:15:51 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	putting_values(t_val *input, char *todie, char *toeat, char *tosleep)
{
	input->to_die = ft_atoi(todie);
	input->to_eat = ft_atoi(toeat);
	input->to_sleep = ft_atoi(tosleep);
	if (input->opt_meals == 0)
		input->opt_meals = -2;
	return (0);
}

int	philosophers(t_val *input, char *todie, char *toeat, char *tosleep)
{
	putting_values(input, todie, toeat, tosleep);
	creating_threads(input);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_val	*input;

	if (argc <= 4 || argc >= 7)
		return (write (1, "Error\n", 6), 1);
	while (argc > 1)
	{
		if (check_for_input(argv[argc - 1], (argc - 1)) == 1)
			return (write (1, "Error\n", 6), 1);
		argc--;
	}
	input = malloc(sizeof(t_val));
	if (input == NULL)
		return (write (1, "Error\n", 6), 1);
	input->philo = ft_atoi(argv[1]);
	if (argv[5] != NULL && ft_atoi(argv[5]) != 0)
		input->opt_meals = ft_atoi(argv[5]);
	if (argv[5] != NULL && ft_atoi(argv[5]) == 0)
		input->opt_meals = -1;
	else
		input->opt_meals = 0;
	if (philosophers(input, argv[2], argv[3], argv[4]) == 1)
		return (1);
	return (0);
}
