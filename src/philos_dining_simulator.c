/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_dining_simulator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:25:17 by sawang            #+#    #+#             */
/*   Updated: 2023/05/07 20:09:58 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_kill_status(struct s_philo *philo)
{
	pthread_mutex_lock(&philo->table->traffic_light.mutex_kill);
	if (philo->table->traffic_light.kill == KILL)
	{
		pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
	return (false);
}

static void	*philo_routine(struct s_philo *philo)
{
	pthread_mutex_lock(&philo->table->traffic_light.mutex_start);
	if (philo->table->traffic_light.start != START)
	{
		pthread_mutex_unlock(&philo->table->traffic_light.mutex_start);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->table->traffic_light.mutex_start);
	philo->start_time = time_now();
	pthread_mutex_lock(&philo->table->mutex_check_eat);
	philo->last_eat = 0;
	pthread_mutex_unlock(&philo->table->mutex_check_eat);
	philo->status = THINKING;
	if (philo->id % 2 == 1)
		sleep_better(philo->table->input.time_to_eat / 2);
	while (check_kill_status(philo) == false)
		philo_activity(philo);
	return (NULL);
}

bool	philo_dining_simulation(struct s_table *table)
{
	unsigned int	i;

	pthread_mutex_lock(&table->traffic_light.mutex_start);
	i = 0;
	while (i < table->input.num_of_philos)
	{
		if (pthread_create(&table->philo_holding.philo_thrs[i], NULL, \
		(void *(*)(void *)) philo_routine, \
		(void *)&table->philo_holding.philos[i]) != 0)
			return (exit_when_pthr_create_failed(table, i), EXIT_FAILURE);
		i++;
	}
	if (pthread_create(&table->death, NULL, \
	(void *(*)(void *)) death_routine, (void *)table) != 0)
		return (exit_when_pthr_create_failed(table, i), EXIT_FAILURE);
	table->traffic_light.start = START;
	pthread_mutex_unlock(&table->traffic_light.mutex_start);
	pthread_join(table->death, NULL);
	mutex_destroy_and_free(table, table->input.num_of_philos);
	return (EXIT_SUCCESS);
}

void	philo_threads_join(struct s_table *table, unsigned int philo_thr_cnt)
{
	unsigned int	i;

	i = 0;
	while (i < philo_thr_cnt)
	{
		pthread_join(table->philo_holding.philo_thrs[i], NULL);
		i++;
	}
}
