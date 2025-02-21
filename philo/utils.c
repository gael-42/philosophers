/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:59:48 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/21 16:37:23 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	size_t			time;
	struct timeval	curr;

	time = 0;
	gettimeofday(&curr, NULL);
	time = (curr.tv_sec * 1000) + (curr.tv_usec / 1000);
	return (time);
}

void	ft_usleep(size_t time, t_philo *ph)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{	
		if (check_finish(ph))
			usleep(time / 1000);
		else
			return ;
	}
}

void	mutex_print(char *message, t_philo *ph)
{
	size_t	time;

	if (!check_finish(ph))
		return ;
	time = get_time() - ph->arg->start_t;
	pthread_mutex_lock(&ph->arg->print);
	printf("%zu %d %s\n", time, ph->id, message);
	pthread_mutex_unlock(&ph->arg->print);
}
