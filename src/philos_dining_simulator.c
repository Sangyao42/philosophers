/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_dining_simulator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:25:17 by sawang            #+#    #+#             */
/*   Updated: 2023/04/27 22:30:30 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static t_kill_status	check_kill_status(struct s_philo *philo)
// {
// 	pthread_mutex_lock(&philo->table->traffic_light.mutex_kill);
// 	if (philo->table->traffic_light.kill == KILL)
// 	{
// 		pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
// 		return (KILL);
// 	}
// 	pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
// 	return (INITIALIZED_KILL);
// 	// return (philo->table->traffic_light.kill);
// }

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
	// return (philo->table->traffic_light.kill);
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
	while (check_kill_status(philo) == false)
	{
		pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
		philo_activity(philo);
	}
	pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
	return (NULL);
}

// bool	philo_dining_simulation(struct s_table *table)
// {
// 	unsigned int	i;

// 	pthread_mutex_lock(&table->traffic_light.mutex_start); //????
// 	if (pthread_create(&table->death, NULL, &death_routine, &table) != 0)
// 		return (printf("Error: pthread_create failed"),
// 			pthread_mutex_unlock(&table->traffic_light.mutex_start),
// 			mutex_destroy_and_free(table, table->input.num_of_philos),
// 			EXIT_FAILURE);
// 	i = -1;
// 	while (++i < table->input.num_of_philos)
// 	{
// 		if (pthread_create(&table->philo_holding.philo_thrs[i], NULL,
// 			&philo_routine, &table->philo_holding.philos[i]) != 0)
// 		{
// 			printf("Error: pthread_create failed");
// 			break ;
// 		}
// 	}
// 	if (i == table->input.num_of_philos)
// 		table->traffic_light.start = START;
// 	pthread_mutex_unlock(&table->traffic_light.mutex_start);
// 	philo_threads_join(table, i);//???
// 	pthread_join(table->death, NULL);
// 	mutex_destroy_and_free(table, table->input.num_of_philos);
// }

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
	// philo_threads_join(table, i);
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
