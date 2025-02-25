/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:51:04 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/24 16:41:43 by lemarian         ###   ########.fr       */
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
	int				corpses;
	bool			finish;
}	t_arg;

typedef struct s_philo
{
	int				id;

	pthread_t		thread;
	pthread_t		monitor;

	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;

	pthread_mutex_t	eating;
	size_t			last_meal;
	int				meals;

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
int		eating_even(t_philo *ph);
int		eating_odd(t_philo *ph);
int		check_finish(t_philo *ph);
int		check_max_meals(t_philo *ph);
int		check_last_meal(t_philo *ph);
void	*one_philo(void *arg);
void	print_error(char *error);
int		create_one_thread(t_philo *phil);
#endif