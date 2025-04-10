/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:44:21 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/10 15:04:34 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				meals_eaten;
	long			time_to_eat;
	int				phil_num;
	long			time_to_sleep;
	long			time_to_die;
	sem_t			*fork;
	sem_t			*stop;
	sem_t			*log;
	sem_t			*fork_drawer;
	long			last_time_to_eat;
	long			start_time;
	int				meal_check;
	pthread_t		monitor_thread;
	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	t_philo			*philo;
	sem_t			*fork;
	sem_t			*stop;
	sem_t			*log;
	sem_t			*fork_drawer;
	int				phil_num;
	long			start_time;
	int				meal_check;
}	t_sim;

long	get_current_time(void);
void	init_arg(t_philo *philo, char **argv, int argc, t_sim *sim);
void	log_status(int id, const char	*status, t_philo *philo);
void	ft_usleep(size_t milliseconds);
int		arg_check(int argc, char **argv);
void	routine(t_philo *philo);
int		ft_atoi(const char *str);
void	error_message(int err_num);
void	init_child_prosses(t_philo *philo);
void	init_child(t_philo *philo, char **argv, t_sim *sim);
void	kill_child_prosses(t_philo *philo);

#endif