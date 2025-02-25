/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:36:58 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/24 16:41:30 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_last_meal(t_philo *ph)
{
	int	result;

	result = 1;
	pthread_mutex_lock(&ph->eating);
	if (get_time() - ph->last_meal >= ph->arg->death_t)
		result = 0;
	pthread_mutex_unlock(&ph->eating);
	return (result);
}

int	check_max_meals(t_philo *ph)
{
	int	result;

	result = 1;
	pthread_mutex_lock(&ph->eating);
	if (ph->meals == ph->arg->max_meal)
		result = 0;
	pthread_mutex_unlock(&ph->eating);
	return (result);
}

int	check_finish(t_philo *ph)
{
	int	result;

	result = 1;
	pthread_mutex_lock(&ph->arg->dying);
	if (ph->arg->finish == true)
		result = 0;
	pthread_mutex_unlock(&ph->arg->dying);
	return (result);
}
