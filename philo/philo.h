/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:51:04 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/21 15:19:00 by lemarian         ###   ########.fr       */
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
	int				size;
	size_t			death_t;
	size_t			eat_t;
	size_t			sleep_t;
	size_t			start_t;
	int				max_meal;

	pthread_mutex_t	print;
	pthread_mutex_t	dying;
	int				corpses;//dying
	bool			finish;//dying
}	t_arg;

typedef struct s_philo
{
	int				id;

	pthread_t		thread;
	pthread_t		monitor;

	pthread_mutex_t	r_fork;//this
	pthread_mutex_t	*l_fork;//this

	pthread_mutex_t	eating;
	size_t			last_meal;//eating
	int				meals;//eating

	t_arg			*arg;
}	t_philo;

int		check_arg(char **av);
int		mini_atoi(char *str);
t_philo	*init(int ac, char **av, t_arg *arg, t_philo *phil);
size_t	get_time(void);
int		threading(t_arg *arg, t_philo *phil);
void	ft_usleep(size_t time, t_philo *ph);
void	mutex_print(char *message, t_philo *ph);
int		sleeping(t_philo *ph);
int		eating(t_philo *ph);
#endif