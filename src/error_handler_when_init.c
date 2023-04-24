/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_when_init.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:14:04 by sawang            #+#    #+#             */
/*   Updated: 2023/04/24 14:08:49 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy_and_free_init_wrong(struct s_table *table, \
	unsigned int philo_cnt)
{
	int	i;

	pthread_mutex_destroy(&table->mutex_print);
	if (table->traffic_light.start == INITIALIZED)
	{
		pthread_mutex_destroy(&table->traffic_light.mutex_start);
		table->traffic_light.start = UNINITIALIZED;
	}
	if (table->traffic_light.kill == INITIALIZED)
	{
		pthread_mutex_destroy(&table->traffic_light.mutex_kill);
		table->traffic_light.kill = UNINITIALIZED;
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
