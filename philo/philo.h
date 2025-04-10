/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:44:21 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/11 11:48:56 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				is_eat;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	long			last_time_to_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	pthread_t		monitor_thread;
	pthread_t		*philosopher;
	struct s_philo	*philo;
	int				phil_num;
	long			start_time;
	int				stop_simulation;
	int				meal_check;
	int				meal_count;
	int				total_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_check_mutex;
}	t_sim;

void	*monitor(void *arg);
long	get_current_time(void);
void	log_status(int id, const char	*status, t_sim *sim);
void	ft_usleep(size_t milliseconds, t_sim *sim);
int		arg_check(int argc, char **argv, t_sim *simulation);
void	init_arg(t_philo *philo, char **argv, t_sim *simulation);
void	*routine(void *arg);
int		ft_atoi(const char *str);
int		init_thread(t_philo *philo, t_sim *simulation);
int		mutex_init(t_sim *simulation);
int		init_all(t_sim *simulation, char **argv);
void	destroy_free(t_sim *simulation, t_philo *philo);
void	error_and_free(t_sim *sim, char *message);
int		read_value(t_sim *sim);
int		read_sim(t_sim *sim);
void	kill_the_philo(t_philo *philos, t_sim *sim, int i);

#endif