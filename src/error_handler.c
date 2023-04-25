/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:14:04 by sawang            #+#    #+#             */
/*   Updated: 2023/04/25 22:40:59 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy_and_free(struct s_table *table, \
	unsigned int philo_cnt)
{
	unsigned int	i;

	pthread_mutex_destroy(&table->mutex_print);
	if (table->traffic_light.start == INITIALIZED_START)
	{
		pthread_mutex_destroy(&table->traffic_light.mutex_start);
		table->traffic_light.start = UNINITIALIZED_START;
	}
	if (table->traffic_light.kill == INITIALIZED_KILL)
	{
		pthread_mutex_destroy(&table->traffic_light.mutex_kill);
		table->traffic_light.kill = UNINITIALIZED_KILL;
	}
	i = 0;
	while (i < philo_cnt)
	{
		pthread_mutex_destroy(&table->philo_holding.mutex_forks[i]);
		i++;
	}
	if (table->philo_holding.philos != NULL)
		free(table->philo_holding.philos);
}
