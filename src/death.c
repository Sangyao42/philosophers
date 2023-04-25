/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:15:01 by sawang            #+#    #+#             */
/*   Updated: 2023/04/25 18:50:06 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(struct s_philo *philo)
{
	unsigned int	i;

	if (time_passed(philo->start_time) - philo->last_eat > \
		philo->table->input.time_to_die)
	{
		print_status(philo, "died");
		return (true);
	}
	i = 0;
	while (i < philo->table->input.num_of_philos)
	{
		if (philo->table->philo_holding.philos[i].eat_cnt < \
			philo->table->input.num_of_must_eat \
			&& philo->table->input.num_of_must_eat != -1)
			return (false);
		i++;
	}
	print_status(philo, "all philos ate enough");
	return (true);
}

void	*death_routine(struct s_table *table)
{
	unsigned int	i;

	pthread_mutex_lock(&table->traffic_light.mutex_start);
	if (table->traffic_light.start != START)
	{
		pthread_mutex_unlock(&table->traffic_light.mutex_start);
		return (NULL);
	}
	while (1)
	{
		i = 0;
		while (i < table->input.num_of_philos)
		{
			pthread_mutex_lock(&table->traffic_light.mutex_kill);
			if (check_dead(&table->philo_holding.philos[i]) == true)
			{
				table->traffic_light.kill = KILL;
				pthread_mutex_unlock(&table->traffic_light.mutex_kill);
				return ;// return (i);
			}
			pthread_mutex_unlock(&table->traffic_light.mutex_kill);
			i++;
		}
	}
	// sleep_better(1);
}
