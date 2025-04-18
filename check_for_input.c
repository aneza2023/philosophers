/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:29:16 by ahavrank          #+#    #+#             */
/*   Updated: 2025/04/17 20:09:10 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] == 32) || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	result = result * sign;
	return (result);
}

int	check_for_input(char *argv, int id)
{
	int	nb;
	int	i;

	i = 0;
	nb = ft_atoi(argv);
	if (nb <= 0 && id < 5)
		return (1);
	if (nb < 0 && id == 5)
		return (1);
	while (argv[i] != '\0')
	{
		if ((argv[i] < '0' || argv[i] > '9') && argv[i] != '+')
			return (1);
		if (argv[i] == '+' && i != 0)
			return (1);
		i++;
	}
	return (0);
}
