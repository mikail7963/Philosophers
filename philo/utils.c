/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:24:11 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/10 15:09:22 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	log_status(int id, const char	*status, t_sim *sim)
{
	long	timestamp;

	pthread_mutex_lock(&sim->log_mutex);
	timestamp = get_current_time() - sim->start_time;
	if (read_sim(sim) == 0)
		printf("%ld %d %s\n", timestamp, id, status);
	pthread_mutex_unlock(&sim->log_mutex);
}

void	kill_the_philo(t_philo *philos, t_sim *sim, int i)
{
	long	time;

	pthread_mutex_lock(&sim->death_check_mutex);
	philos->sim->stop_simulation = 1;
	time = (get_current_time() - philos->sim->start_time);
	printf("%ld %d died\n", time, philos[i].id);
	pthread_mutex_unlock(&sim->death_check_mutex);
}

int	read_value(t_sim *sim)
{
	int	value;

	pthread_mutex_lock(&sim->meal_mutex);
	value = sim->total_meal;
	pthread_mutex_unlock(&sim->meal_mutex);
	return (value);
}

int	read_sim(t_sim *sim)
{
	int	value;

	pthread_mutex_lock(&sim->death_check_mutex);
	value = sim->stop_simulation;
	pthread_mutex_unlock(&sim->death_check_mutex);
	return (value);
}
