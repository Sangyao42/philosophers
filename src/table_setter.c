/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:08:03 by sawang            #+#    #+#             */
/*   Updated: 2023/05/08 16:47:07 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	set_traffic_light(struct s_table *table)
{
	table->traffic_light.start = UNINITIALIZED_START;
	table->traffic_light.kill = UNINITIALIZED_KILL;
	if (pthread_mutex_init(&table->traffic_light.mutex_start, NULL) != 0)
	{
		printf("Error: Mutex init failed");
		return (EXIT_FAILURE);
	}
	table->traffic_light.start = INITIALIZED_START;
	if (pthread_mutex_init(&table->traffic_light.mutex_kill, NULL) != 0)
	{
		printf("Error: Mutex init failed");
		return (EXIT_FAILURE);
	}
	table->traffic_light.kill = INITIALIZED_KILL;
	return (EXIT_SUCCESS);
}

//malloc the mutexes (fork and check_eat) at once??
// and init them at once as well
// check if *2 needed
unsigned int	set_philo_holding(struct s_table *table)
{
	unsigned int	i;

	i = 0;
	table->philo_holding.philos = \
		ft_calloc(table->input.num_of_philos, (sizeof(struct s_philo)));
	table->philo_holding.philo_thrs = \
		ft_calloc(table->input.num_of_philos, (sizeof(pthread_t)));
	table->philo_holding.mutex_forks = \
		ft_calloc(table->input.num_of_philos, (sizeof(pthread_mutex_t)));
	table->philo_holding.mutex_array_check_eat = \
		ft_calloc(table->input.num_of_philos, (sizeof(pthread_mutex_t)));
	if (!table->philo_holding.philos || !table->philo_holding.philo_thrs \
		|| !table->philo_holding.mutex_forks || \
		!table->philo_holding.mutex_array_check_eat)
		return (printf("Error: Malloc failed"), i);
	while (i < table->input.num_of_philos)
	{
		if (pthread_mutex_init(&table->philo_holding.mutex_forks[i], NULL) \
			!= 0)
			return (printf("Error: %dth forks Mutex init failed", i), i);
		i++;
	}
	return (i);
}

void	sit_philos(struct s_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->input.num_of_philos)
	{
		table->philo_holding.philos[i].id = i + 1;
		table->philo_holding.philos[i].mutex_l_fork = \
			&table->philo_holding.mutex_forks[i];
		table->philo_holding.philos[i].mutex_r_fork = \
			&table->philo_holding.mutex_forks[(i + 1) \
			% table->input.num_of_philos];
		table->philo_holding.philos[i].eat_cnt = 0;
		table->philo_holding.philos[i].mutex_check_eat = \
			&table->philo_holding.mutex_array_check_eat[i];
		table->philo_holding.philos[i].table = table;
		i++;
	}
}

bool	set_table(struct s_table *table, int argc, char *argv[])
{
	unsigned int	philo_cnt;

	if (set_input(table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&table->mutex_print, NULL) != 0)
		return (printf("Error: Mutex init failed"), EXIT_FAILURE);
	// if (pthread_mutex_init(&table->mutex_check_eat, NULL) != 0)
	// 	return (printf("Error: Mutex init failed"), \
	// 		pthread_mutex_destroy(&table->mutex_print), EXIT_FAILURE);
	if (set_traffic_light(table) == EXIT_FAILURE)
		return (mutex_destroy_and_free(table, 0), EXIT_FAILURE);
	philo_cnt = set_philo_holding(table);
	if (philo_cnt != table->input.num_of_philos)
	{
		mutex_destroy_and_free(table, philo_cnt);
		return (EXIT_FAILURE);
	}
	sit_philos(table);
	return (EXIT_SUCCESS);
}
