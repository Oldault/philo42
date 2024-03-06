/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:42:48 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/06 17:31:29 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	i = data->phil_num;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (1);
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = data->phil_num;
	while (--i >= 0)
	{
		data->philos[i].id = i;
		data->philos[i].x_ate = 0;
		data->philos[i].l_fork_id = i;
		data->philos[i].r_fork_id = (i + 1) % data->phil_num;
		data->philos[i].prev_meal_time = 0;
		data->philos[i].data = data;
	}
	return (0);
}

void	*init_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (write(2, "Invalid Argument Amount 🙅\n", 29), NULL);
	if (found_alph(av + 1))
		return (write(2, "Invalid Argument Given 🙈\n", 28), NULL);
	data->phil_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->num_phil_eat = INT_MAX;
	if (ac == 6)
		data->num_phil_eat = ft_atoi(av[5]);
	if (data->phil_num < 2 || data->phil_num > 200)
	{
		write(2, "No table available for that amount of Philosophers\n", 52);
		return (NULL);
	}
	if (init_mutexes(data))
		return (write(2, "Init mutex Error\n", 17), NULL);
	if (init_philos(data))
		return (write(2, "Init philos Error\n", 18), NULL);
	return ((int *)1);
}
