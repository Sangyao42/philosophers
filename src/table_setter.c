/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:08:03 by sawang            #+#    #+#             */
/*   Updated: 2023/04/25 11:39:39 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	set_philo_holding(struct s_table *table)
{
	unsigned int	i;

	i = 0;
	table->philo_holding.philos = ft_calloc(1 * (sizeof(struct s_philo) + \
	sizeof(pthread_t) + sizeof(pthread_mutex_t)) * table->input.num_of_philos);
	if (table->philo_holding.philos == NULL)
		return (ft_printf("Error: Malloc failed"), i);
	table->philo_holding.philo_thrs = table->philo_holding.philos \
		+ (sizeof(struct s_philo) * table->input.num_of_philos);
	table->philo_holding.mutex_forks = table->philo_holding.philos \
		+ (sizeof(struct s_philo) * table->input.num_of_philos) \
		+ (sizeof(pthread_t) * table->input.num_of_philos);
	while (i < table->input.num_of_philos)
	{
		if (pthread_mutex_init(&table->philo_holding.mutex_forks[i], NULL) \
			!= 0)
			return (ft_printf("Error: Mutex init failed"), i);
		i++;
	}
	return (i);
}

bool	set_traffic_light(struct s_table *table)
{
	table->traffic_light.start = UNINITIALIZED;
	table->traffic_light.kill = UNINITIALIZED;
	if (pthread_mutex_init(&table->traffic_light.mutex_start, NULL) != 0)
	{
		ft_printf("Error: Mutex init failed");
		return (EXIT_FAILURE);
	}
	table->traffic_light.start = INITIALIZED;
	if (pthread_mutex_init(&table->traffic_light.mutex_kill, NULL) != 0)
	{
		ft_printf("Error: Mutex init failed");
		return (EXIT_FAILURE);
	}
	table->traffic_light.kill = INITIALIZED;
	return (EXIT_SUCCESS);
}

void	sit_philos(struct s_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.num_of_philos)
	{
		table->philo_holding.philos[i].id = i + 1;
		table->philo_holding.philos[i].mutex_l_fork = \
			&table->philo_holding.mutex_forks[i];
		table->philo_holding.philos[i].mutex_r_fork = \
			&table->philo_holding.mutex_forks[(i + 1) \
			% table->input.num_of_philos];
		// table->philo_holding.philos[i]. last_eat = 0;//get_time();??
		table->philo_holding.philos[i].eat_cnt = 0;
		table->philo_holding.philos[i].table = table;
		i++;
	}
}

bool	set_table(struct s_table *table, int argc, char *argv[])
{
	int	philo_cnt;

	if (set_input(&table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&table->mutex_print, NULL) != 0)
		return (ft_printf("Error: Mutex init failed"), EXIT_FAILURE);
	if (set_traffic_light(&table) == EXIT_FAILURE)
		return (mutex_destroy_and_free(&table, 0), EXIT_FAILURE);
	philo_cnt = set_philo_holding(&table);
	if (philo_cnt != table->input.num_of_philos)
	{
		mutex_destroy_and_free(&table, philo_cnt);
		return (EXIT_FAILURE);
	}
	sit_philos(&table);
	return (EXIT_SUCCESS);
}
