/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:44:38 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/07 17:58:38 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

// -- STRUCTS -- //
struct	s_data;

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
	int				time_to_think;
	int				num_phil_eat;
	int				amount_to_eat;
	int				died_flag;
	int				all_ate_flag;
	long long		timestamp;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	meal_check;
	pthread_mutex_t	writing;
	pthread_mutex_t	all_ate;
	pthread_mutex_t	death_flag;
}					t_data;

// --- UTILS --- //
int					ft_atoi(const char *str);
int					found_alph(char **arr);
long long			timestamp(void);
void				ft_sleep(t_data *data, long long time);
long long			time_diff(long long past, long long pres);
int					all_ate_flag(t_data *data);
int					someone_died(t_data *data);

// --- INIT ---- //
void				*init_data(t_data *data, int ac, char **av);

// -- ACTIONS -- //
void				try_to_eat(t_philo *philo);
void				*routines(void *param_philo);

// --- EXIT ---- //
void				exit_if_needed(t_data *data, t_philo *philo);
void				join_threads(t_data *data, t_philo *philos);

// --- PRINT --- //
void				error(char *str);
void				log_action(t_data *data, char *emoji, int phil_id,
						char *str);
void				print_death(t_data *data, int phil_id);
void				print_header(void);

#endif
