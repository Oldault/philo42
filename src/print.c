/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:34:02 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/07 17:31:42 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_data *data, char *emoji, int phil_id, char *str)
{
	pthread_mutex_lock(&(data->writing));
	if (!(someone_died(data)) && !(all_ate_flag(data)))
	{
		if (emoji)
			printf("\033[35;1m[%s]\033[0m\t", emoji);
		printf("\033[34m%lli\033[0m\t", timestamp() - data->timestamp);
		printf("\033[32;1;4m%i\033[0m ", phil_id + 1);
		printf("\033[33;3m%s\033[0m\n", str);
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

void	print_death(t_data *data, int phil_id)
{
	pthread_mutex_lock(&(data->writing));
	printf("\n\x1b[30;41;1;4m[ 💀🪦      Philosopher %d Died      🪦 💀 ]\x1b[0m\n",
		phil_id + 1);
	printf("\x1b[31;49;1m░ ▒░▓  ░░▒▓███▀▒░ ░▒ ▒  ░░▒▒ ▓░▒░▒░ ▒░▒░▒░\n");
	printf("░ ░ ▒  ░▒░▒   ░   ░  ▒   ░░▒ ▒ ░ ▒  ░ ▒ ▒░\n");
	printf("  ░ ░    ░    ░ ░        ░ ░ ░ ░ ░░ ░ ░ ▒ \n");
	printf("    ░  ░ ░      ░ ░        ░ ░        ░ ░ \n");
	printf("              ░ ░        ░                \n\n");
	printf("\x1b[0m\n");
	pthread_mutex_unlock(&(data->writing));
}

void	print_header(void)
{
	printf("\n\033[30;45;1m Icon \t\033[30;44;1m Time \t\033[30;42;1m ID ");
	printf("\t\033[30;43;1m Action \033[0m\n\n");
}
