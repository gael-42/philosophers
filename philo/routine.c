/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:07:59 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/21 15:10:51 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *ph)
{
	if (ph->arg->finish == true)
		return (0);
	pthread_mutex_lock(&ph->r_fork);
	mutex_print("has picked up a fork", ph);
	pthread_mutex_lock(ph->l_fork);
	mutex_print("has picked up a fork", ph);
	pthread_mutex_lock(&ph->eating);
	ph->last_meal = get_time();
	ph->meals++;//data race here?
	printf("philo %d meals %d\n", ph->id, ph->meals);
	mutex_print("is eating", ph);
	pthread_mutex_unlock(&ph->eating);
	ft_usleep(ph->arg->eat_t, ph);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(&ph->r_fork);
	return (1);
}

int	sleeping(t_philo *ph)
{
	if (ph->arg->finish == true)
		return (0);
	mutex_print("is sleeping", ph);
	ft_usleep(ph->arg->sleep_t, ph);
	mutex_print("is thinking", ph);
	return (1);
}
