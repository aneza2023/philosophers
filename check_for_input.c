/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:29:16 by ahavrank          #+#    #+#             */
/*   Updated: 2025/06/04 16:05:37 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	long int	result;

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

int	numb_int(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		i;

	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	string = malloc(numb_int(n) * sizeof(char) + 1);
	if (string == NULL)
		return (NULL);
	if (n < 0)
		string[i] = '-';
	i = numb_int(n);
	string[i] = '\0';
	i--;
	while (n != 0)
	{
		if (n < 0)
			n = n * (-1);
		string[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (string);
}

int another_check(char *orig, long int nb)
{
	char *new;

	new = ft_itoa(nb);
	if (ft_strcmp(orig, new) != 0)
		return (free(new), 1);
	return (free(new), 0);
}

int	check_for_input(char *argv, int id)
{
	long int	nb;
	int	i;

	i = 0;
	nb = ft_atoi(argv);
	if (another_check(argv, nb) == 1)
		return (1);
	if (nb > 2147483647 || nb < -2147483648)
		return (1);
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
