/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:15:01 by sawang            #+#    #+#             */
/*   Updated: 2023/05/09 22:41:53 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_kill_signal(struct s_table *table)
{
	pthread_mutex_lock(&table->traffic_light.mutex_kill);
	table->traffic_light.kill = KILL;
	pthread_mutex_unlock(&table->traffic_light.mutex_kill);
}

static bool	check_dead(struct s_philo *philo)
{
	pthread_mutex_lock(philo->mutex_check_eat);
	if (philo->last_eat != 0 && \
		time_passed(philo->last_eat) > philo->table->input.time_to_die)
	{
		pthread_mutex_unlock(philo->mutex_check_eat);
		set_kill_signal(philo->table);
		return (true);
	}
	pthread_mutex_unlock(philo->mutex_check_eat);
	return (false);
}

static bool	check_eaten(struct s_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->input.num_of_philos)
	{
		pthread_mutex_lock(table->philo_holding.philos[i].mutex_check_eat);
		if (table->philo_holding.philos[i].eat_cnt < \
			table->input.num_of_must_eat)
		{
			pthread_mutex_unlock(table->\
			philo_holding.philos[i].mutex_check_eat);
			return (false);
		}
		pthread_mutex_unlock(table->philo_holding.philos[i].mutex_check_eat);
		i++;
	}
	set_kill_signal(table);
	return (true);
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
				print_status(&table->philo_holding.philos[i], "died");
				return (NULL);
			}
			i++;
		}
		if (check_eaten(table) == true)
		{
			print_status(&table->philo_holding.philos[i - 1], \
				"all philos ate enough");
			return (NULL);
		}
	}
}
