/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:39:42 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/10 14:41:49 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	while (1)
	{
		if ((get_current_time() - philo->last_time_to_eat) \
			>= philo->time_to_die)
		{
			time = get_current_time() - philo->start_time;
			sem_wait(philo->log);
			printf("%ld %d is dead\n", time, philo->id);
			sem_post(philo->stop);
		}
		if ((philo->meals_eaten >= philo->meal_check + 2)
			&& philo->meal_check > 0)
			sem_post(philo->stop);
		usleep(1000);
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	if (pthread_create(&(philo->monitor_thread), NULL, monitor, philo) != 0)
		return ;
	while (1)
	{
		log_status(philo->id, "is thinking", philo);
		sem_wait(philo->fork_drawer);
		sem_wait(philo->fork);
		sem_post(philo->fork_drawer);
		log_status(philo->id, "has taken a fork", philo);
		sem_wait(philo->fork_drawer);
		sem_wait(philo->fork);
		sem_post(philo->fork_drawer);
		log_status(philo->id, "has taken a fork", philo);
		log_status(philo->id, "is eating", philo);
		philo->last_time_to_eat = get_current_time();
		philo->meals_eaten++;
		ft_usleep(philo->time_to_eat);
		sem_post(philo->fork);
		sem_post(philo->fork);
		log_status(philo->id, "is sleeping", philo);
		ft_usleep(philo->time_to_sleep);
	}
}
