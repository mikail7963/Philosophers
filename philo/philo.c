/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:48:11 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/10 12:20:41 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_free(t_sim *simulation, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < simulation->phil_num)
		pthread_mutex_destroy(&simulation->forks[i++]);
	pthread_mutex_destroy(&simulation->log_mutex);
	pthread_mutex_destroy(&simulation->death_check_mutex);
	free(philo);
	free(simulation->philosopher);
	free(simulation->forks);
	free(simulation);
}

int	main(int argc, char **argv)
{
	t_sim	*simulation;
	int		i;

	simulation = malloc(sizeof(t_sim));
	if (!simulation)
		return (0);
	memset(simulation, 0, sizeof(t_sim));
	if (arg_check(argc, argv, simulation))
		return (0);
	simulation->philo = malloc(sizeof(t_philo) * simulation->phil_num);
	simulation->forks = malloc(sizeof(pthread_mutex_t) * simulation->phil_num);
	simulation->philosopher = malloc(sizeof(pthread_t) * simulation->phil_num);
	if (!simulation->philo || !simulation->forks || !simulation->philosopher)
		return (0);
	if (init_all(simulation, argv))
		return (0);
	if (pthread_create(&(simulation->monitor_thread), \
	NULL, monitor, simulation) != 0)
		return (error_and_free(simulation, "pthread create error"), 1);
	i = 0;
	while (i < simulation->phil_num)
		pthread_join(simulation->philosopher[i++], NULL);
	pthread_join(simulation->monitor_thread, NULL);
	destroy_free(simulation, simulation->philo);
	return (0);
}
