/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:34:03 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/06 18:56:59 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_to_eat(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->l_fork_id]));
	log_action(data, "⬅️🍴 ", philo->id, "took the fork on his left");
	pthread_mutex_lock(&(data->forks[philo->r_fork_id]));
	log_action(data, " 🍴➡️", philo->id, "took the fork on his right");
	pthread_mutex_lock(&(data->meal_check));
	log_action(data, " 🍝 ", philo->id, "is eating");
	philo->prev_meal_time = timestamp();
	pthread_mutex_unlock(&(data->meal_check));
	ft_sleep(data, data->time_to_eat);
	(philo->x_ate)++;
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
	while(!(data->died_flag))
	{
		try_to_eat(philo);
		if (data->all_ate_flag)
			break ;
		log_action(data, " 💤 ", philo->id, "is sleeping");
		ft_sleep(data, data->time_to_sleep);
		log_action(data, " 💭 ", philo->id, "is thinking");
	}
	return (NULL);
}

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
			if (time_diff(philo[i].prev_meal_time, timestamp()) > data->time_to_die)
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
	t_philo *philos;

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
	printf("\n\033[30;45;1m Icon \t\033[30;44;1m Time \t\033[30;42;1m ID \t\033[30;43;1m Action \033[0m\n\n");
	if (start_threads(&data))
		return (error("Problem with Threads"), 1);
	return (0);
}
