/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:22:56 by lemarian          #+#    #+#             */
/*   Updated: 2024/11/12 16:19:23 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	size_t	time;
	struct timeval	curr;

	time = 0;
	gettimeofday(&curr, NULL);
	time = (curr.tv_sec * 1000) + (curr.tv_usec / 1000);
	return (time);
}

void	ft_usleep(size_t time, t_arg *arg)
{
	size_t	start;

	if (arg->finish == 1)
		usleep(100);
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}

int	check_finish(t_philo *ph)
{
	pthread_mutex_lock(&ph->arg->dead);
	if (ph->arg->finish == 1)
	{
		pthread_mutex_unlock(&ph->arg->dead);
		return (0);
	}
	pthread_mutex_unlock(&ph->arg->dead);
	return (1);
}

void	mutex_print(char *message, t_philo *ph)
{
	size_t	time;

	if (check_finish(ph) == 0)
		return;
	time = get_time();
	ft_usleep(2, ph->arg);
	pthread_mutex_lock(&ph->arg->write);
	printf("%zu %d %s\n", time, ph->id, message);
	pthread_mutex_unlock(&ph->arg->write);
}
