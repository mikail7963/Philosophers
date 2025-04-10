/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:33:12 by mikkayma          #+#    #+#             */
/*   Updated: 2025/02/13 13:46:47 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	result;

	index = -1;
	result = 0;
	while (str[++index] != '\0')
	{
		if (str[index] < '0' || str[index] > '9')
			return (-1);
	}
	index = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = (result * 10) + (str[index] - 48);
		index++;
	}
	return (result);
}

void	error_message(int err_num, t_sim *sim)
{
	if (err_num == 0)
	{
		printf("Usage: number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
	if (err_num == 1)
		printf("invalid number of philosophers\n");
	if (err_num == 2)
		printf("invalid time_to_die\n");
	if (err_num == 3)
		printf("invalid time_to_eat\n");
	if (err_num == 4)
		printf("invalid time_to_sleep\n");
	if (err_num == 5)
		printf("invalid number_of_times_each_philosopher_must_eat\n");
	free(sim);
}

int	arg_check(int argc, char **argv, t_sim *simulation)
{
	int	a;

	if (argc != 5 && argc != 6)
		return (error_message(0, simulation), 1);
	a = 1;
	while (a < 5)
	{
		if (ft_atoi(argv[a]) < 0 || !ft_atoi(argv[a]))
			return (error_message(a, simulation), 1);
		a++;
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0 || ft_atoi(argv[5]) == 0)
			return (error_message(5, simulation), 1);
		simulation->meal_check = ft_atoi(argv[5]);
	}
	simulation->phil_num = ft_atoi(argv[1]);
	return (0);
}
