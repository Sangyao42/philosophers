/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:08:03 by sawang            #+#    #+#             */
/*   Updated: 2023/04/23 22:49:17 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_philo_holding(struct s_philo_holding *philo_holding)
{
	int	i;

	i = 0;
	philo_holding->philos = fit_calloc(1 * (sizeof(struct s_philo) + \
	sizeof(pthread_t) + sizeof(pthread_mutex_t)) * table->input.num_of_philos);
	if (philo_holding->philos == NULL)
		return (ft_printf("Error: Malloc failed"), EXIT_FAILURE);
	while (i < table->input.num_of_philos)
	//
}

int	set_traffic_light(struct s_traffic_light *traffic_light)
{
	if (pthread_mutex_init(&traffic_light->mutex_start, NULL) != 0)
		return (ft_printf("Error: Mutex init failed"), EXIT_FAILURE);
	if (pthread_mutex_init(&traffic_light->mutex_kill, NULL) != 0)
		return (ft_printf("Error: Mutex init failed"), EXIT_FAILURE);
	traffic_light->start = 0;
	traffic_light->kill = 0;
	return (EXIT_SUCCESS);
}

bool	set_table(struct s_table *table, int argc, char *argv[])
{
	if (pthread_mutex_init(&table->mutex_print, NULL) != 0)
		return (ft_printf("Error: Mutex init failed"), EXIT_FAILURE);
	// if () pthread_mutex_init(&table->traffic_light.mutex_start, NULL) != 0
	// 	|| pthread_mutex_init(&table->traffic_light.mutex_kill, NULL) != 0)
	// 	return (ft_printf("Error: Mutex init failed"), EXIT_FAILURE);
	// table->traffic_light.start = 0;
	// table->traffic_light.kill = 0;
	if(set_traffic_light(&table->traffic_light) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (set_input(&table->input, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (set_philo_holding(&table->philo_holding) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

