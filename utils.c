/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:22:56 by lemarian          #+#    #+#             */
/*   Updated: 2024/11/09 18:03:24 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	long int	time;
	struct timeval	curr;

	time = 0;
	gettimeofday(&curr, NULL);
	time = (curr.tv_sec * 1000) + (curr.tv_usec / 1000);
	return (time);
}

int	check_dead(t_philo *ph)
{
	if (ph->dead == 1)
		return (0);
	if (ph->arg->done == 1)
		return (0);
	return (1);
}

void	mutex_print(char *message, t_philo *ph)
{
	if (!check_dead(ph))
		return;
	pthread_mutex_lock(&ph->arg->write);
	printf("%ld %d %s\n", get_time(), ph->id, message);
	pthread_mutex_unlock(&ph->arg->write);
}
