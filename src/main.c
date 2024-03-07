/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:34:03 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/07 17:57:42 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = data->philos;
	data->timestamp = timestamp();
	while (++i < data->phil_num)
	{
		philos[i].prev_meal_time = timestamp();
		if (pthread_create(&(philos[i].th_id), NULL, routines, &(philos[i])))
			return (1);
	}
	exit_if_needed(data, philos);
	join_threads(data, philos);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(&data, ac, av) == NULL)
		return (1);
	print_header();
	if (start_threads(&data))
		return (error("Problem with Threads"), 1);
	return (0);
}
