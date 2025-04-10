/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:44:38 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/10 14:47:44 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_arg(t_philo *philo, char **argv, int argc, t_sim *sim)
{
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0)
			return (error_message(5));
		sim->meal_check = ft_atoi(argv[5]);
	}
	else
		sim->meal_check = 0;
	philo->phil_num = ft_atoi(argv[1]);
	sem_unlink("/my_fork");
	sem_unlink("/stop");
	sem_unlink("/log");
	sem_unlink("/fork_drawer");
	sim->fork = sem_open("/my_fork", O_CREAT, 0644, ft_atoi(argv[1]));
	sim->log = sem_open("/log", O_CREAT, 0644, 1);
	sim->stop = sem_open("/stop", O_CREAT, 0644, 0);
	sim->fork_drawer = sem_open("/fork_drawer", O_CREAT, 0644, 1);
}

void	init_child_prosses(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->phil_num)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
		{
			printf("fork error\n");
			exit (1);
		}
		if (philo[i].pid == 0)
			routine(&philo[i]);
		usleep(500);
		i++;
	}
}

void	init_child(t_philo *philo, char **argv, t_sim *sim)
{
	int		i;

	sim->start_time = get_current_time();
	i = 0;
	while (i < philo->phil_num)
	{
		philo[i].meal_check = sim->meal_check;
		philo[i].meals_eaten = 0;
		philo[i].last_time_to_eat = sim->start_time;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].id = i + 1;
		philo[i].stop = sim->stop;
		philo[i].fork_drawer = sim->fork_drawer;
		philo[i].log = sim->log;
		philo[i].start_time = sim->start_time;
		philo[i].fork = sim->fork;
		i++;
	}
	init_child_prosses(philo);
	sem_wait(sim->stop);
	kill_child_prosses(philo);
}
