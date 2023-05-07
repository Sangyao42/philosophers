/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:42:42 by sawang            #+#    #+#             */
/*   Updated: 2023/05/07 16:56:39 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(struct s_philo *philo, char *doing)
{
	pthread_mutex_lock(&philo->table->mutex_print);
	pthread_mutex_lock(&philo->table->traffic_light.mutex_kill);
	if (philo->table->traffic_light.kill != KILL)
	{
		if (philo_strcmp(doing, "all philos ate enough") == 0)
			printf("%lu %s\n", time_passed(philo->start_time), doing);
		else
			printf("%lu %d %s\n", time_passed(philo->start_time), \
				philo->id, doing);
	}
	pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
	pthread_mutex_unlock(&philo->table->mutex_print);
}
