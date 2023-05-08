/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:15:01 by sawang            #+#    #+#             */
/*   Updated: 2023/05/08 16:17:42 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

// static bool	check_dead(struct s_philo *philo)
// {
// 	unsigned int	i;

// 	pthread_mutex_lock(&philo->table->mutex_check_eat);
// 	if (philo->last_eat != 0 && \
// 		time_passed(philo->last_eat) > philo->table->input.time_to_die)
// 	{
// 		print_status(philo, "died");
// 		return (pthread_mutex_unlock(&philo->table->mutex_check_eat), true);
// 	}
// 	i = 0;
// 	while (i < philo->table->input.num_of_philos)
// 	{
// 		if (philo->table->philo_holding.philos[i].eat_cnt < \
// 			philo->table->input.num_of_must_eat)
// 			return (pthread_mutex_unlock(&philo->table->mutex_check_eat), \
// 			false);
// 		i++;
// 	}
// 	if (i == philo->table->input.num_of_philos)
// 	{
// 		print_status(philo, "all philos ate enough");
// 		return (pthread_mutex_unlock(&philo->table->mutex_check_eat), true);
// 	}
// 	return (pthread_mutex_unlock(&philo->table->mutex_check_eat), false);
// }

static bool	check_dead(struct s_philo *philo)
{
	unsigned int	i;

	pthread_mutex_lock(&philo->table->mutex_check_eat);
	if (philo->last_eat != 0 && \
		time_passed(philo->last_eat) > philo->table->input.time_to_die)
	{
		print_status(philo, "died");
		return (pthread_mutex_unlock(&philo->table->mutex_check_eat), true);
	}
	i = 0;
	while (i < philo->table->input.num_of_philos)
	{
		if (philo->table->philo_holding.philos[i].eat_cnt < \
			philo->table->input.num_of_must_eat)
			return (pthread_mutex_unlock(&philo->table->mutex_check_eat), \
			false);
		i++;
	}
	if (i == philo->table->input.num_of_philos)
	{
		print_status(philo, "all philos ate enough");
		return (pthread_mutex_unlock(&philo->table->mutex_check_eat), true);
	}
	return (pthread_mutex_unlock(&philo->table->mutex_check_eat), false);
}

void	*death_routine(struct s_table *table)
{
	unsigned int	i;

	pthread_mutex_lock(&table->traffic_light.mutex_start);
	if (table->traffic_light.start != START)
		return (pthread_mutex_unlock(&table->traffic_light.mutex_start), NULL);
	pthread_mutex_unlock(&table->traffic_light.mutex_start);
	while (1)
	{
		i = 0;
		while (i < table->input.num_of_philos)
		{
			if (check_dead(&table->philo_holding.philos[i]) == true)
			{
				pthread_mutex_lock(&table->traffic_light.mutex_kill);
				table->traffic_light.kill = KILL;
				pthread_mutex_unlock(&table->traffic_light.mutex_kill);
				print_status(&table->philo_holding.philos[i], "died");
				philo_threads_join(table, table->input.num_of_philos);
				return (NULL);
			}
			i++;
		}
	}
}
