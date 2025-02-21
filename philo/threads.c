/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:38:17 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/21 15:11:12 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	ft_usleep(ph->arg->death_t, ph);
	while (1)
	{
		if (ph->arg->finish == true || ph->meals == ph->arg->max_meal)//data race here?
			return (NULL);
		if (get_time() - ph->last_meal >= ph->arg->death_t)
		{
			pthread_mutex_lock(&ph->arg->dying);
			ph->arg->finish = true;
			ph->arg->corpses++;
			pthread_mutex_unlock(&ph->arg->dying);
			if (ph->arg->corpses < 2)
			{
				pthread_mutex_lock(&ph->arg->print);
				printf("%ld %d has died\n", get_time() - ph->arg->start_t, ph->id);//too long
				pthread_mutex_unlock(&ph->arg->print);
			}
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
	while (ph->arg->finish == false)
	{
		if (!eating(ph))
			break ;
		if (!sleeping(ph))
			break ;
		if (ph->arg->max_meal != -1 && ph->meals == ph->arg->max_meal)
			return (NULL);
	}
	return (NULL);
}

int	threading(t_arg *arg, t_philo *phil)//protect functions?
{
	int	i;

	i = 0;
	while (i < arg->size)
	{
		pthread_create(&phil[i].thread, NULL, start, &phil[i]);
		pthread_create(&phil[i].monitor, NULL, monitor, &phil[i]);
		i++;
	}
	i = 0;
	while (i < arg->size)
	{
		pthread_join(phil[i].monitor, NULL);
		pthread_join(phil[i].thread, NULL);
		i++;
	}
	return (1);
}
