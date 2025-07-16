/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:19:41 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/11 18:14:02 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(200);
}

void	one_philo(t_sim *sim, t_philo *philo)
{
	log_status(philo->id, "is thinking", sim);
	log_status(philo->id, "has taken a fork", sim);
	ft_usleep(philo->time_to_die);
	printf("%ld %d died\n", (get_current_time() - sim->start_time), \
	philo->id);
	sim->stop_simulation = 1;
	return ;
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		log_status(philo->id, "has taken a fork", philo->sim);
		pthread_mutex_lock(philo->right_fork);
		log_status(philo->id, "has taken a fork", philo->sim);
	}
	else
	{
		usleep(120);
		pthread_mutex_lock(philo->right_fork);
		log_status(philo->id, "has taken a fork", philo-> sim);
		pthread_mutex_lock(philo->left_fork);
		log_status(philo->id, "has taken a fork", philo->sim);
	}
}

void	eat(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	take_forks(philo);
	log_status(philo->id, "is eating", sim);
	pthread_mutex_lock(&sim->meal_mutex);
	philo->meals_eaten++;
	sim->total_meal++;
	philo->last_time_to_eat = get_current_time();
	pthread_mutex_unlock(&sim->meal_mutex);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	if (sim->phil_num == 1)
	{
		one_philo(sim, philo);
		return (NULL);
	}
	while (read_sim(sim) == 0)
	{
		log_status(philo->id, "is thinking", sim);
		eat(philo);
		log_status(philo->id, "is sleeping", sim);
		ft_usleep(philo->time_to_sleep);
	}
	return (NULL);
}
