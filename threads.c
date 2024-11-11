/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:51:21 by lemarian          #+#    #+#             */
/*   Updated: 2024/11/09 18:01:52 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		usleep(ph->arg->death_t * 1000);
		if (ph->last_meal - ph->arg->death_t >= 0)
		{
			mutex_print("has died", ph);
			pthread_mutex_lock(&ph->death);
			ph->dead = 1;
			pthread_mutex_unlock(&ph->death);
			pthread_mutex_lock(&ph->arg->dead);
			ph->arg->done = 1;
			pthread_mutex_unlock(&ph->arg->dead);
			break;
		}
	}
	mutex_print("Return monitor", ph);
	return (NULL);
}

void	sleeping(t_philo *ph)
{
	mutex_print("is sleeping", ph);
	usleep(ph->arg->sleep_t * 1000);
	if (!check_dead(ph))
		return;
	mutex_print("is thinking", ph);
}

void	eating(t_philo *ph)
{
	if (!check_dead(ph))
		return;
	pthread_mutex_lock(&ph->r_fork);
	mutex_print("has picked up a fork", ph);
	pthread_mutex_lock(ph->l_fork);
	mutex_print("has picked up a fork", ph);
	mutex_print("is eating", ph);
	pthread_mutex_lock(&ph->eating);
	ph->last_meal = get_time();
	ph->meals++;
	pthread_mutex_unlock(&ph->eating);
	usleep(ph->arg->eat_t * 1000);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(&ph->r_fork);
}

void	*start(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 != 0)
		usleep(2000);
	while (1)
	{
		if (!check_dead(ph) || ph->meals == ph->arg->max_meal)
			break;
		eating(ph);
		if (!check_dead(ph))
			break;
		sleeping(ph);
		pthread_detach(ph->monitor);
	}
	mutex_print("Return philo", ph);
	return (NULL);
}

int	threading(t_data *a)
{
	int	i;

	i = 0;
	while (i < a->arg->size)
	{
		pthread_create(&a->phil[i].thread, NULL, start, &a->phil[i]);
		pthread_create(&a->phil[i].monitor, NULL, monitor, &a->phil[i]);
		i++;
	}
	i = 0;
	while (i < a->arg->size)
	{
		pthread_join(a->phil[i].monitor, NULL);
		pthread_join(a->phil[i].thread, NULL);
		i++;
	}
	printf("done\n");
	return (1);
}
