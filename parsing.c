/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:42:47 by lemarian          #+#    #+#             */
/*   Updated: 2024/11/08 14:20:00 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	negative;

	i = 0;
	nb = 0;
	negative = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative *= -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * negative);
}

int	check_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-')
			if (str[i] < '0' || str[i] > '9')
				return (0);
		i++;
	}
	return (1);
}

int	check_arg(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!check_is_num(av[i]))
		{
			printf("Argument can only be numbers\n");
			return (0);
		}
		if (i == 1 && ft_atoi(av[i]) > 200)
		{
			printf("Max number of philosophers is 200\n");
			return (0);
		}
		if (ft_atoi(av[i]) <= 0 && i != 5)
		{
			printf("Arguments must be greater than 0\n");
			return (0);
		}
		if (i == 5 && ft_atoi(av[i]) < 0)
		{
			printf("Number of meals cannot be less than 0\n");
			return (0);
		}
		i++;
	}
	return (1);
}
