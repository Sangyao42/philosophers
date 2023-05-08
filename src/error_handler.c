/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:14:04 by sawang            #+#    #+#             */
/*   Updated: 2023/05/08 16:23:56 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy_and_free(struct s_table *table, \
	unsigned int philo_cnt)
{
	unsigned int	i;

	pthread_mutex_destroy(&table->mutex_print);
	// pthread_mutex_destroy(&table->mutex_check_eat);
	if (table->traffic_light.start != UNINITIALIZED_START)
		pthread_mutex_destroy(&table->traffic_light.mutex_start);
	if (table->traffic_light.kill != UNINITIALIZED_KILL)
		pthread_mutex_destroy(&table->traffic_light.mutex_kill);
	i = 0;
	while (i < philo_cnt)
	{
		pthread_mutex_destroy(&table->philo_holding.mutex_forks[i]);
		i++;
	}
	if (table->philo_holding.philos != NULL)
		free(table->philo_holding.philos);
	if (table->philo_holding.philo_thrs != NULL)
		free(table->philo_holding.philo_thrs);
	if (table->philo_holding.mutex_forks != NULL)
		free(table->philo_holding.mutex_forks);
	if (table->philo_holding.mutex_array_check_eat != NULL)
		free(table->philo_holding.mutex_array_check_eat);
}

void	exit_when_pthr_create_failed(struct s_table *table, \
	unsigned int philo_thr_cnt)
{
	printf("Error: pthread_create of death failed");
	pthread_mutex_unlock(&table->traffic_light.mutex_start);
	philo_threads_join(table, philo_thr_cnt);
	mutex_destroy_and_free(table, table->input.num_of_philos);
}
