/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:42:48 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/08 10:55:57 by svolodin         ###   ########.fr       */
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
		data->philos[i].prev_meal_time = 0;
		data->philos[i].data = data;
		data->philos[i].l_fork_id = i;
		data->philos[i].r_fork_id = (i + 1) % data->phil_num;
	}
	return (0);
}

static void	get_input_data(t_data *data, char **av)
{
	data->phil_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time_to_think = time_diff(data->time_to_sleep, data->time_to_eat) + 1;
	data->num_phil_eat = INT_MAX;
}

void	*init_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (error("Invalid Argument Amount 🙅"), NULL);
	if (found_alph(av + 1))
		return (error("Invalid Argument Given 🙈"), NULL);
	get_input_data(data, av);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0)
			return (error("No meals to be eaten"), NULL);
		data->num_phil_eat = ft_atoi(av[5]);
	}
	if (data->phil_num < 1 || data->phil_num > 200)
	{
		error("No table available for that amount of Philosophers");
		return (NULL);
	}
	if (init_mutexes(data))
		return (error("Init mutex Error"), NULL);
	if (init_philos(data))
		return (error("Init philos Error"), NULL);
	return ((int *)1);
}
