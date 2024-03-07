/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:17:40 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/07 17:52:35 by svolodin         ###   ########.fr       */
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
	pthread_mutex_destroy(&(data->meal_check));
	pthread_mutex_destroy(&(data->all_ate));
}

static void	check_death(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->phil_num && !(someone_died(data))
		&& !(all_ate_flag(data)))
	{
		pthread_mutex_lock(&(data->meal_check));
		if (time_diff(philo[i].prev_meal_time, timestamp()) > data->time_to_die)
		{
			print_death(data, i);
			pthread_mutex_lock(&(data->death_flag));
			data->died_flag = 1;
			pthread_mutex_unlock(&(data->death_flag));
		}
		pthread_mutex_unlock(&(data->meal_check));
		usleep(100);
	}
}

void	exit_if_needed(t_data *data, t_philo *philo)
{
	int	i;

	while (!(all_ate_flag(data)))
	{
		check_death(data, philo);
		if (someone_died(data) || all_ate_flag(data))
			break ;
		i = 0;
		while (i < data->phil_num && philo[i].x_ate >= data->num_phil_eat)
			i++;
		if (i == data->phil_num)
		{
			pthread_mutex_lock(&(data->all_ate));
			data->all_ate_flag = 1;
			pthread_mutex_unlock(&(data->all_ate));
		}
	}
}
