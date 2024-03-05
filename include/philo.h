/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:44:38 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/05 12:09:59 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

// -- STRUCTS -- //
struct s_data;

typedef struct s_philo
{
	int				id;
	int				x_ate;
	int				l_fork_id;
	int				r_fork_id;
	long long		prev_meal_time;
	struct s_data	*data;
	pthread_t		th_id;
}					t_philo;

typedef struct s_data
{
	int				phil_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_phil_eat;
	int				amount_eaten;
	int				died_flag;
	int				all_ate_flag;
	t_philo			philos[200];
}					t_data;

// --- UTILS --- //
int					ft_atoi(const char *str);
int					found_alph(char **arr);

#endif