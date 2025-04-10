/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:07:24 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/10 15:09:29 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/time.h>

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(1000);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	log_status(int id, const char	*status, t_philo *philo)
{
	long	timestamp;

	sem_wait(philo->log);
	timestamp = get_current_time() - philo->start_time;
	printf("%ld %d %s\n", timestamp, id, status);
	sem_post(philo->log);
}
