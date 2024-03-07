/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:34:03 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/07 10:17:32 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->phil_num)
		pthread_join(philos[i].th_id, NULL);
	i = -1;
	while (++i < data->phil_num)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->writing));
}

void	check_casualties(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->all_ate_flag))
	{
		i = -1;
		while (++i < data->phil_num && !(data->died_flag))
		{
			pthread_mutex_lock(&(data->meal_check));
			if (time_diff(philo[i].prev_meal_time,
					timestamp()) > data->time_to_die)
			{
				print_death(data, i);
				data->died_flag = 1;
			}
			pthread_mutex_unlock(&(data->meal_check));
			usleep(100);
		}
		if (data->died_flag)
			break ;
		i = 0;
		while (i < data->phil_num && philo[i].x_ate >= data->num_phil_eat)
			i++;
		if (i == data->phil_num)
			data->all_ate_flag = 1;
	}
}

int	start_threads(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = data->philos;
	data->timestamp = timestamp();
	while (++i < data->phil_num)
	{
		if (pthread_create(&(philos[i].th_id), NULL, routines, &(philos[i])))
			return (1);
		philos[i].prev_meal_time = timestamp();
	}
	check_casualties(data, philos);
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
