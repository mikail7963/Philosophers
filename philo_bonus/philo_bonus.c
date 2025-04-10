/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:57:31 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/13 17:17:28 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_child_prosses(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->phil_num)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}

void	free_sem_philo(t_philo *philo, t_sim *sim)
{
	sem_unlink("/my_fork");
	sem_unlink("/stop");
	sem_unlink("/log");
	sem_unlink("/fork_drawer");
	sem_close(philo->fork);
	sem_close(philo->log);
	sem_close(philo->stop);
	sem_close(philo->fork_drawer);
	free(philo);
	free(sim);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;
	int		phil_num;

	arg_check(argc, argv);
	phil_num = ft_atoi(argv[1]);
	sim = malloc(sizeof(t_sim));
	sim->philo = malloc(sizeof(t_philo) * phil_num);
	if (!sim)
	{
		printf("Malloc error\n");
		return (0);
	}
	init_arg(sim->philo, argv, argc, sim);
	init_child(sim->philo, argv, sim);
	free_sem_philo(sim->philo, sim);
}
