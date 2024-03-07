/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:54:50 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/07 17:54:53 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_ate_flag(t_data *data)
{
	pthread_mutex_lock(&(data->all_ate));
	if (data->all_ate_flag)
	{
		pthread_mutex_unlock(&(data->all_ate));
		return (1);
	}
	pthread_mutex_unlock(&(data->all_ate));
	return (0);
}

int	someone_died(t_data *data)
{
	pthread_mutex_lock(&(data->death_flag));
	if (data->died_flag)
	{
		pthread_mutex_unlock(&(data->death_flag));
		return (1);
	}
	pthread_mutex_unlock(&(data->death_flag));
	return (0);
}
