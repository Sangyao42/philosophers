/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_philo_simulator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:06:10 by sawang            #+#    #+#             */
/*   Updated: 2023/05/08 15:13:09 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*lonely_philo_routine(struct s_philo *philo)
{
	// philo->start_time = time_now();
	philo->table->start_time = time_now();
	pthread_mutex_lock(philo->mutex_l_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->mutex_l_fork);
	sleep_better(philo->table->input.time_to_die);
	print_status(philo, "died");
	return (NULL);
}

int	lonely_philo_simulator(struct s_table *table)
{
	if (pthread_create(&table->philo_holding.philo_thrs[0], NULL, \
		(void *(*)(void *)) lonely_philo_routine, \
		(void *) &table->philo_holding.philos[0]) != 0)
		return (printf("Error: pthread_create failed"), \
			mutex_destroy_and_free(table, 1), EXIT_FAILURE);
	pthread_join(table->philo_holding.philo_thrs[0], NULL);
	mutex_destroy_and_free(table, 1);
	return (EXIT_SUCCESS);
}
