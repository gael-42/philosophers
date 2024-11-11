/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:40:25 by lemarian          #+#    #+#             */
/*   Updated: 2024/11/09 17:56:27 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	a;

	if (!check_arg(av))
		return (1);
	if (!init(ac, av, &a))
		return (1);
	if (!threading(&a))
		return (1);
	free(a.phil);
	free(a.arg);
	return (0);
}//need to free a.phil
