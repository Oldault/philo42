/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:17:40 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/07 17:16:50 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_to_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(data->forks[philo->r_fork_id]));
		log_action(data, " 🍴➡️", philo->id, "took the fork on his right");
		pthread_mutex_lock(&(data->forks[philo->l_fork_id]));
		log_action(data, "⬅️🍴 ", philo->id, "took the fork on his left");
	}
	else
	{
		pthread_mutex_lock(&(data->forks[philo->l_fork_id]));
		log_action(data, "⬅️🍴 ", philo->id, "took the fork on his left");
		pthread_mutex_lock(&(data->forks[philo->r_fork_id]));
		log_action(data, " 🍴➡️", philo->id, "took the fork on his right");
	}
	pthread_mutex_lock(&(data->meal_check));
	log_action(data, " 🍝 ", philo->id, "is eating");
	philo->prev_meal_time = timestamp();
	(philo->x_ate)++;
	pthread_mutex_unlock(&(data->meal_check));
	ft_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&(data->forks[philo->l_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->r_fork_id]));
}

void	*routines(void *param_philo)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)param_philo;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (!(someone_died(data)))
	{
		try_to_eat(philo);
		if (all_ate_flag(data))
			break ;
		log_action(data, " 💤 ", philo->id, "is sleeping");
		ft_sleep(data, data->time_to_sleep);
		log_action(data, " 💭 ", philo->id, "is thinking");
		ft_sleep(data, data->time_to_think);
	}
	return (NULL);
}
