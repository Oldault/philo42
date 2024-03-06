/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:44:38 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/06 10:43:47 by svolodin         ###   ########.fr       */
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
	int				amount_to_eat;
	int				died_flag;
	int				all_ate_flag;
	long long		timestamp;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	meal_check;
	pthread_mutex_t	writing;
}					t_data;

// --- UTILS --- //
int					ft_atoi(const char *str);
int					found_alph(char **arr);

// --- INIT ---- //
void				*init_data(t_data *data, int ac, char **av);

#endif