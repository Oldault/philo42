/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:34:02 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/06 17:34:41 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_data *data, char *emoji ,int phil_id, char *str)
{
	pthread_mutex_lock(&(data->writing));
	if (!(data->died_flag))
	{
		if (emoji)
			printf("[%s]\t", emoji);
		printf("%lli\t", timestamp() - data->timestamp);
		printf("%i ", phil_id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(data->writing));
}

void	error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	write(2, "\n", 2);
}
