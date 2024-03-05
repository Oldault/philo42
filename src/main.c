/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:34:03 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/05 12:11:27 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*init_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Invalid Argument Amount 🙅😬🤷\n"), NULL);
	if (found_alph(av + 1))
		return (printf("Invalid Argument Given 🙈😩😑\n"), NULL);
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
	return ((int*)1);
}

int	main(int ac, char **av)
{
	t_data data;
	
	if (init_data(&data, ac, av) == NULL)
		return (1);
	printf("All works well\n");
	return (0);
}
