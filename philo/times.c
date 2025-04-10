/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:24:11 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/10 15:09:22 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

int	meal_check(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	if (read_value(sim) >= sim->phil_num * sim->meal_check)
	{
		pthread_mutex_lock(&sim->death_check_mutex);
		sim->stop_simulation = 1;
		pthread_mutex_unlock(&sim->death_check_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (!read_sim(sim) && sim->phil_num > 1)
	{
		i = -1;
		while (++i < sim->phil_num)
		{
			pthread_mutex_lock(&sim->meal_mutex);
			if (get_current_time() - sim->philo[i].last_time_to_eat \
			>= sim->philo[i].time_to_die)
			{
				pthread_mutex_unlock(&sim->meal_mutex);
				kill_the_philo(sim->philo, sim, i);
				return (NULL);
			}
			pthread_mutex_unlock(&sim->meal_mutex);
		}
		if (sim->meal_check > 0 && meal_check(sim->philo))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
