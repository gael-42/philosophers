/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:07:29 by lemarian          #+#    #+#             */
/*   Updated: 2024/11/12 14:26:08 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *param)
{
	t_philo	*ph;

	ph = (t_philo *)param;
	while (1)
	{
		ft_usleep(ph->arg->death_t, ph->arg);
		if (!check_finish(ph)|| ph->meals == ph->arg->max_meal)
			break;
		if (get_time() - ph->last_meal > ph->arg->death_t)
		{
			if (!check_finish(ph))
				break;
			pthread_mutex_lock(&ph->arg->dead);
			ph->arg->finish = true;
			pthread_mutex_unlock(&ph->arg->dead);
			pthread_mutex_lock(&ph->arg->write);
			printf("%ld %d has died\n", get_time(), ph->id);
			pthread_mutex_unlock(&ph->arg->write);
			break;
		}
	}
	return (NULL);
}

void	sleeping(t_philo *ph)
{
	if (!check_finish(ph))
		return;
	mutex_print("is sleeping", ph);
	ft_usleep(ph->arg->sleep_t, ph->arg);
	mutex_print("is thinking", ph);
}

void	eating(t_philo *ph)
{
	if (!check_finish(ph))
		return;
	pthread_mutex_lock(&ph->r_fork);
	mutex_print("has picked up a fork", ph);
	pthread_mutex_lock(ph->l_fork);
	mutex_print("has picked up a fork", ph);
	pthread_mutex_lock(&ph->eating);
	ph->last_meal = get_time();
	ph->meals++;
	mutex_print("is eating", ph);
	pthread_mutex_unlock(&ph->eating);
	ft_usleep(ph->arg->eat_t, ph->arg);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(&ph->r_fork);
}

void	*start(void *param)
{
	t_philo	*ph;

	ph = (t_philo *)param;
	if (ph->id % 2 != 0)
		ft_usleep(ph->arg->eat_t, ph->arg);
	while (1)
	{
		if (!check_finish(ph))
			break;
		if (ph->meals == ph->arg->max_meal)
			break;
		eating(ph);
		sleeping(ph);
	}
	return (NULL);
}

int	threading(t_data *a)
{
	int	i;

	i = 0;
	while (i < a->arg->size)
	{
		pthread_create(&a->ph[i].thread, NULL, start, &a->ph[i]);
		pthread_create(&a->ph[i].monitor, NULL, monitor, &a->ph[i]);
		i++;
	}
	i = 0;
	while (i < a->arg->size)
	{
		pthread_join(a->ph[i].monitor, NULL);
		pthread_join(a->ph[i].thread, NULL);
		i++;
	}
	return (1);
}
