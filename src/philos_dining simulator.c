/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_dining simulator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:25:17 by sawang            #+#    #+#             */
/*   Updated: 2023/04/25 19:04:46 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	philo_dining_simulation(struct s_table *table)
// {
// 	unsigned int	i;

// 	pthread_mutex_lock(&table->traffic_light.mutex_start); //????
// 	if (pthread_create(&table->death, NULL, &death_routine, &table) != 0)
// 		return (ft_printf("Error: pthread_create failed"), \
// 			pthread_mutex_unlock(&table->traffic_light.mutex_start), \
// 			mutex_destoy_and_free(table, table->input.num_of_philos), \
// 			EXIT_FAILURE);
// 	i = -1;
// 	while (++i < table->input.num_of_philos)
// 	{
// 		if (pthread_create(&table->philo_holding.philo_thrs[i], NULL, \
// 			&philo_routine, &table->philo_holding.philos[i]) != 0)
// 		{
// 			ft_printf("Error: pthread_create failed");
// 			break ;
// 		}
// 	}
// 	if (i == table->input.num_of_philos)
// 		table->traffic_light.start = START;
// 	pthread_mutex_unlock(&table->traffic_light.mutex_start);
// 	philo_threads_join(table, i);//???
// 	pthread_join(table->death, NULL);
// 	mutex_destoy_and_free(table, table->input.num_of_philos);
// }

bool	philo_dining_simulation(struct s_table *table)
{
	unsigned int	i;

	pthread_mutex_lock(&table->traffic_light.mutex_start);
	if (pthread_create(&table->death, NULL, &death_routine, &table) != 0)
		return (ft_printf("Error: pthread_create failed"), \
			pthread_mutex_unlock(&table->traffic_light.mutex_start), \
			mutex_destoy_and_free(table, table->input.num_of_philos), \
			EXIT_FAILURE);
	i = -1;
	while (++i < table->input.num_of_philos)
	{
		if (pthread_create(&table->philo_holding.philo_thrs[i], NULL, \
			&philo_routine, &table->philo_holding.philos[i]) != 0)
			return (ft_printf("Error: pthread_create failed"), \
				pthread_mutex_unlock(&table->traffic_light.mutex_start), \
				philo_threads_join(table, i), pthread_join(table->death, NULL), \
				mutex_destoy_and_free(table, table->input.num_of_philos), \
				EXIT_FAILURE);
	}
	if (i == table->input.num_of_philos)
		table->traffic_light.start = START;
	pthread_mutex_unlock(&table->traffic_light.mutex_start);
	philo_threads_join(table, i);
	pthread_join(table->death, NULL);
	mutex_destoy_and_free(table, table->input.num_of_philos);
	return (EXIT_SUCCESS);
}

void	*philo_routine(struct s_philo *philo)
{
	pthread_mutex_lock(&philo->table->traffic_light.mutex_start);
	if (philo->table->traffic_light.start != START)
	{
		pthread_mutex_unlock(&philo->table->traffic_light.mutex_start);
		return ;//???
	}
	pthread_mutex_unlock(&philo->table->traffic_light.mutex_start);
	philo->start_time = time_now();
	philo->last_eat = time_now();
	philo->status = THINKING;
	while (1)
	{
		while (check_kill_status(philo) != KILL)
		{
			pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
			philo_activity(philo);
		}
		pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
		// philo_die(philo);
		return ;
	}
}

t_kill_status	check_kill_status(struct s_philo *philo)
{
	pthread_mutex_lock(&philo->table->traffic_light.mutex_kill);
	// if (philo->table->traffic_light.kill == KILL)
	// 	pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
	// return (KILL);
	return (philo->table->traffic_light.kill);
}

void	philo_threads_join(struct s_table *table, int i)
{
	while (i > 0)
	{
		pthread_join(table->philo_holding.philo_thrs[i - 1], NULL);
		i--;
	}
}
