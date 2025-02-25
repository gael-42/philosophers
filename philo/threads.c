/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:38:17 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/25 11:28:10 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*ph;
	size_t	start;

	ph = (t_philo *)arg;
	ft_usleep(ph->arg->death_t, ph);
	start = ph->arg->start_t;
	while (1)
	{
		if (!check_finish(ph) || !check_max_meals(ph))
			return (NULL);
		if (!check_last_meal(ph))
		{
			pthread_mutex_lock(&ph->arg->dying);
			ph->arg->finish = true;
			ph->arg->corpses++;
			if (ph->arg->corpses < 2)
			{
				pthread_mutex_lock(&ph->arg->print);
				printf("%ld %d died\n", get_time() - start, ph->id);
				pthread_mutex_unlock(&ph->arg->print);
			}
			pthread_mutex_unlock(&ph->arg->dying);
			return (NULL);
		}
	}
}

void	*start(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 != 0)
		ft_usleep(ph->arg->eat_t / 2, ph);
	while (check_finish(ph))
	{
		if (ph->id % 2 == 0)
		{
			if (!eating_even(ph))
				break ;
		}
		else
		{
			if (!eating_odd(ph))
				break ;
		}
		if (!sleeping(ph))
			break ;
		if (ph->arg->max_meal != -1 && !check_max_meals(ph))
			return (NULL);
	}
	return (NULL);
}

int	create_one_thread(t_philo *phil)
{
	if (pthread_create(&phil[0].thread, NULL, one_philo, &phil[0]) != 0)
		return (print_error("failed to create thread"), 0);
	if (pthread_join(phil[0].thread, NULL) != 0)
		return (print_error("failed to join thread"), 0);
	return (1);
}

int	threading(t_arg *arg, t_philo *phil)
{
	int	i;

	i = 0;
	while (i < arg->size)
	{
		if (pthread_create(&phil[i].thread, NULL, start, &phil[i]) != 0)
			return (print_error("failed to create thread"), 0);
		if (pthread_create(&phil[i].monitor, NULL, monitor, &phil[i]) != 0)
			return (print_error("failed to create thread"), 0);
		i++;
	}
	i = 0;
	while (i < arg->size)
	{
		if (pthread_join(phil[i].monitor, NULL) != 0)
			return (print_error("failed to join thread"), 0);
		if (pthread_join(phil[i].thread, NULL) != 0)
			return (print_error("failed to join thread"), 0);
		i++;
	}
	return (1);
}
