/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:25:50 by ahavrank          #+#    #+#             */
/*   Updated: 2025/05/30 18:02:38 by ahavrank         ###   ########.fr       */
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
	if (allocate_for_threads(input) == 1)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_val	*input;

	if (argc <= 4 || argc >= 7)
		return (write (1, "invalid\n", 8), 1);
	while (argc > 1)
	{
		if (check_for_input(argv[argc - 1], (argc - 1)) == 1)
			return (write (1, "invalid\n", 8), 1);
		argc--;
	}
	input = malloc(sizeof(t_val));
	if (input == NULL)
		return (write (1, "invalid\n", 8), 1);
	input->philo = ft_atoi(argv[1]);
	if (argv[5] != NULL && ft_atoi(argv[5]) != 0)
		input->opt_meals = ft_atoi(argv[5]);
	else if (argv[5] != NULL && ft_atoi(argv[5]) == 0)
		return (0);
	else
		input->opt_meals = 0;
	if (philosophers(input, argv[2], argv[3], argv[4]) == 1)
		return (free(input), 1);
	free(input);
	return (0);
}

// for input, could be changed based on requirements
// input->opt_meals = -1, pokud nb of meals 0 >> confusion