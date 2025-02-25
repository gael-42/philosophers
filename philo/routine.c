/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:07:59 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/24 16:12:48 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_even(t_philo *ph)
{
	if (!check_finish(ph))
		return (0);
	pthread_mutex_lock(&ph->r_fork);
	mutex_print("has picked up a fork", ph);
	pthread_mutex_lock(ph->l_fork);
	mutex_print("has picked up a fork", ph);
	pthread_mutex_lock(&ph->eating);
	ph->last_meal = get_time();
	ph->meals++;
	mutex_print("is eating", ph);
	pthread_mutex_unlock(&ph->eating);
	ft_usleep(ph->arg->eat_t, ph);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(&ph->r_fork);
	return (1);
}

int	eating_odd(t_philo *ph)
{
	if (!check_finish(ph))
		return (0);
	pthread_mutex_lock(ph->l_fork);
	mutex_print("has picked up a fork", ph);
	pthread_mutex_lock(&ph->r_fork);
	mutex_print("has picked up a fork", ph);
	pthread_mutex_lock(&ph->eating);
	ph->last_meal = get_time();
	ph->meals++;
	mutex_print("is eating", ph);
	pthread_mutex_unlock(&ph->eating);
	pthread_mutex_unlock(&ph->r_fork);
	ft_usleep(ph->arg->eat_t, ph);
	pthread_mutex_unlock(ph->l_fork);
	return (1);
}

int	sleeping(t_philo *ph)
{
	if (!check_finish(ph))
		return (0);
	mutex_print("is sleeping", ph);
	ft_usleep(ph->arg->sleep_t, ph);
	mutex_print("is thinking", ph);
	return (1);
}

void	*one_philo(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	pthread_mutex_lock(&ph->r_fork);
	mutex_print("has taken a fork", ph);
	ft_usleep(ph->arg->death_t, ph);
	mutex_print("has died", ph);
	pthread_mutex_unlock(&ph->r_fork);
	return (NULL);
}
