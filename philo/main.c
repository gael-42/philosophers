/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:51:18 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/18 14:05:35 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_arg	arg;
	t_philo	*phil;

	phil = NULL;
	if (!check_arg(av))
		return (1);
	phil = init(ac, av, &arg, phil);
	if (!phil)
		return (1);
	if (!threading(&arg, phil))
		return (free(phil), 1);
	free(phil);
	return (0);
}
