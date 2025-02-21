/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:57:39 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/18 14:07:01 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mini_atoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

int	check_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
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
			printf("Arguments can only be positive numbers\n");
			return (0);
		}
		if (i == 1 && mini_atoi(av[i]) > 200)
		{
			printf("Max number of philosophers is 200\n");
			return (0);
		}
		if (mini_atoi(av[i]) == 0 && i != 5)
		{
			printf("Arguments must be greater than 0\n");
			return (0);
		}
		i++;
	}
	return (1);
}
