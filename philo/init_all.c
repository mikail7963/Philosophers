/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:28:08 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/10 12:54:41 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_and_free(t_sim *sim, char *message)
{
	printf("%s\n", message);
	destroy_free(sim, sim->philo);
}

int	init_thread(t_philo *philo, t_sim *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->phil_num)
	{
		pthread_mutex_init(&simulation->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < simulation->phil_num)
	{
		philo[i].left_fork = &simulation->forks[i];
		philo[i].right_fork = &simulation->forks[(i + 1) % \
			simulation->phil_num];
		if (pthread_create(&simulation->philosopher[i], \
		NULL, routine, &philo[i]) != 0)
			return (error_and_free(simulation, "pthread create error"), 1);
		usleep(1);
		i++;
	}
	return (0);
}

void	init_arg(t_philo *philo, char **argv, t_sim *simulation)
{
	int	i;

	i = 0;
	simulation->stop_simulation = 0;
	simulation->total_meal = 0;
	simulation->start_time = get_current_time();
	while (i < simulation->phil_num)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		philo[i].sim = simulation;
		philo[i].meals_eaten = 0;
		philo[i].last_time_to_eat = simulation->start_time;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].id = i + 1;
		i++;
	}
}

int	mutex_init(t_sim *simulation)
{
	int	log_mutex;
	int	meal_mutex;
	int	death_mutex;

	log_mutex = pthread_mutex_init(&simulation->log_mutex, NULL);
	meal_mutex = pthread_mutex_init(&simulation->meal_mutex, NULL);
	death_mutex = pthread_mutex_init(&simulation->death_check_mutex, NULL);
	if (log_mutex != 0 || meal_mutex != 0 || death_mutex != 0)
	{
		printf("mutex error\n");
		return (1);
	}
	return (0);
}

int	init_all(t_sim *simulation, char **argv)
{
	init_arg(simulation->philo, argv, simulation);
	if (mutex_init(simulation))
		return (1);
	if (init_thread(simulation->philo, simulation))
		return (1);
	return (0);
}
