/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:38:24 by lemarian          #+#    #+#             */
/*   Updated: 2024/11/09 15:16:57 by lemarian         ###   ########.fr       */
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

typedef struct s_arg
{
	int				size;
	long int		death_t;
	long int		eat_t;
	long int		sleep_t;
	int				max_meal;
	int				done;

	pthread_mutex_t	write;
	pthread_mutex_t	dead;
}	t_arg;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_t		monitor;

	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;

	t_arg			*arg;
	int				meals;
	int				dead;
	pthread_mutex_t	death;

	pthread_mutex_t	eating;
	long int		last_meal;
}	t_philo;

typedef struct s_data
{
	t_philo	*phil;
	t_arg	*arg;
}	t_data;

int	check_arg(char **av);
int	ft_atoi(const char *str);
int	init(int ac, char **av, t_data *a);
int	threading(t_data *a);
int	check_dead(t_philo *ph);
long int	get_time(void);
void	mutex_print(char *message, t_philo *ph);

#endif
