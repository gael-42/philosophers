/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:32:06 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/18 14:07:37 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_phil(t_arg *arg, t_philo *phil)
{
	int	i;

	i = 0;
	while (i < arg->size)
	{
		phil[i].id = i + 1;
		phil[i].arg = arg;
		phil[i].meals = 0;
		phil[i].last_meal = 0;
		pthread_mutex_init(&phil[i].r_fork, NULL);
		pthread_mutex_init(&phil[i].eating, NULL);
		if (arg->size == 1)
			phil[0].l_fork = &phil[0].r_fork;
		else if (i + 1 == arg->size)
			phil[i].l_fork = &phil[0].r_fork;
		else
			phil[i].l_fork = &phil[i + 1].r_fork;
		i++;
	}
}

void	init_arg(int ac, char **av, t_arg *arg)
{
	arg->size = mini_atoi(av[1]);
	arg->death_t = mini_atoi(av[2]);
	arg->eat_t = mini_atoi(av[3]);
	arg->sleep_t = mini_atoi(av[4]);
	arg->start_t = get_time();
	arg->finish = false;
	arg->corpses = 0;
	if (ac > 5)
		arg->max_meal = mini_atoi(av[5]);
	else
		arg->max_meal = -1;
	pthread_mutex_init(&arg->print, NULL);
	pthread_mutex_init(&arg->dying, NULL);
}

t_philo	*init(int ac, char **av, t_arg *arg, t_philo *phil)
{
	init_arg(ac, av, arg);
	phil = malloc(sizeof(t_philo) * arg->size);
	if (!phil)
	{
		printf("t_philo malloc failed\n");
		return (NULL);
	}
	init_phil(arg, phil);
	return (phil);
}
