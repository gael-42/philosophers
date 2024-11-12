/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:44:54 by lemarian          #+#    #+#             */
/*   Updated: 2024/11/12 16:13:25 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_phil(t_data *a)
{
	int	i;

	i = 0;
	while (i < a->arg->size)
	{
		a->ph[i].id = i + 1;
		a->ph[i].arg = a->arg;
		a->ph[i].meals = 0;
		a->ph[i].last_meal = 0;
		pthread_mutex_init(&a->ph[i].r_fork, NULL);
		pthread_mutex_init(&a->ph[i].eating, NULL);
		if (a->arg->size == 1)
			a->ph[0].l_fork = &a->ph[0].r_fork;
		else if (i + 1 == a->arg->size)
			a->ph[i].l_fork = &a->ph[0].r_fork;
		else
			a->ph[i].l_fork = &a->ph[i + 1].r_fork;
		i++;
	}
}

void	init_arg(int ac, char **av, t_data *a)
{
	a->arg->size = ft_atoi(av[1]);
	a->arg->death_t = ft_atoi(av[2]);
	a->arg->eat_t = ft_atoi(av[3]);
	a->arg->sleep_t = ft_atoi(av[4]);
	a->arg->finish = 0;
	if (ac > 5)
		a->arg->max_meal = ft_atoi(av[5]);
	else
		a->arg->max_meal = -1;
	pthread_mutex_init(&a->arg->write, NULL);
	pthread_mutex_init(&a->arg->dead, NULL);
}

int	init(int ac, char **av, t_data *a)
{
	a->arg = malloc(sizeof(t_arg));
	if (!a->arg)
	{
		printf("Malloc failed\n");
		return (0);
	}
	init_arg(ac, av, a);
	a->ph = malloc(sizeof(t_philo) * a->arg->size);
	if (!a->ph)
	{
		printf("Malloc failed\n");
		return (0);
	}
	init_phil(a);
	return (1);
}
