/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:53:14 by lemarian          #+#    #+#             */
/*   Updated: 2024/11/12 16:13:13 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_arg
{
	int	size;
	size_t	death_t;
	size_t	eat_t;
	size_t	sleep_t;
	int		max_meal;

	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	int		finish;
}	t_arg;

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	pthread_t	monitor;

	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;

	pthread_mutex_t	eating;
	size_t	last_meal;
	int	meals;

	t_arg	*arg;
}	t_philo;


typedef struct s_data
{
	t_philo	*ph;
	t_arg	*arg;
}	t_data;

int	check_arg(char **av);
int	ft_atoi(const char *str);
int	init(int ac, char **av, t_data *a);
int	threading(t_data *a);
size_t	get_time(void);
void	ft_usleep(size_t time, t_arg *arg);
void	mutex_print(char *message, t_philo *ph);
int	check_finish(t_philo *ph);

#endif
