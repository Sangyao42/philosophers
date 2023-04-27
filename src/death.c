/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:15:01 by sawang            #+#    #+#             */
/*   Updated: 2023/04/27 18:02:41 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static bool	check_dead(struct s_philo *philo)
{
	// unsigned int	i;

	if (time_passed(philo->last_eat) > philo->table->input.time_to_die)
	{
		// print_status(philo, "died");
		return (true);
	}
	return (false);
	// i = 0;
	// while (i < philo->table->input.num_of_philos)
	// {
	// 	if (philo->eat_cnt <
	// 		philo->table->input.num_of_must_eat)
	// 		return (false);
	// 	i++;
	// }
	// print_status(philo, "all philos ate enough");
	// return (true);
}

// static bool	check_start(struct s_table *table)
// {
// 	pthread_mutex_lock(&table->traffic_light.mutex_start);
// 	if (table->traffic_light.start == START)
// 	{
// 		pthread_mutex_unlock(&table->traffic_light.mutex_start);
// 		return (true);
// 	}
// 	pthread_mutex_unlock(&table->traffic_light.mutex_start);
// 	return (false);
// }

void	*death_routine(struct s_table *table)
{
	unsigned int	i;

	pthread_mutex_lock(&table->traffic_light.mutex_start);
	if (table->traffic_light.start != START)
	{
		pthread_mutex_unlock(&table->traffic_light.mutex_start);
		return (NULL);
	}
	// usleep(1);
	pthread_mutex_unlock(&table->traffic_light.mutex_start);
	// printf("DEATH THREAD STARTED\n");
	// while (check_start(table) == true)
	while (1)
	{
		i = 0;
		while (i < table->input.num_of_philos)
		{
			pthread_mutex_lock(&table->mutex_check_eat);
			if (check_dead(&table->philo_holding.philos[i]) == true)
			{
				pthread_mutex_lock(&table->traffic_light.mutex_kill);
				table->traffic_light.kill = KILL;
				pthread_mutex_unlock(&table->traffic_light.mutex_kill);
				pthread_mutex_unlock(&table->mutex_check_eat);
				philo_threads_join(table, table->input.num_of_philos);
				print_status(&table->philo_holding.philos[i], "died");
				return (NULL);//????
				// break ;
			}
			pthread_mutex_unlock(&table->mutex_check_eat);
			i++;
		}
	}
	return (NULL);
	// philo_threads_join(table, table->input.num_of_philos);
	// return (NULL);
}
